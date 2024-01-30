#include "ElixirSubsystem.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Runtime/Launch/Resources/Version.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "ElixirSettings.h"
#include "Utils.h"

void UElixirSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	InitializeTimer();
	Instance = GetWorld()->GetGameInstance()->GetSubsystem<UElixirSubsystem>();
}

void UElixirSubsystem::PrepareElixir(FString InApiKey)
{
	ReiKey = "";
	FParse::Value(FCommandLine::Get(), TEXT("-rei"), ReiKey);
	ApiKey = InApiKey;
	BaseURL = GetMutableDefault<UElixirSettings>()->ElixirApiBaseUrl;
}

void UElixirSubsystem::InitElixir(FCallback OnComplete)
{
	// This callback will trigger every time the session refresh timer is exhausted
	SessionTimerCallback.BindLambda([this]
	{
		Refresh([this](bool res) { UE_LOG(LogTemp, Warning, TEXT("RefreshToken")); });
	});

#if UE_BUILD_DEBUG || UE_BUILD_DEVELOPMENT
	if (ReiKey.IsEmpty() && GetMutableDefault<UElixirSettings>()->EnableDeveloperLogin)
	{
		FString Uri = TEXT("/sdk/auth/v2/dev/reikey");
		const FString PlayerIdOverride = GetMutableDefault<UElixirSettings>()->PlayerIdOverride;

		if (!PlayerIdOverride.IsEmpty())
		{
			const FString EscapedPlayerIdOverride = FGenericPlatformHttp::UrlEncode(PlayerIdOverride);
			Uri.Append(FString::Format(TEXT("?playerId={0}"), {*EscapedPlayerIdOverride}));
		}

		MakeRequest(Uri, nullptr, [this, OnComplete](const TSharedPtr<FJsonObject>& JsonObject)
		            {
			            const TSharedPtr<FJsonObject> Data = ConvertSnakeCaseToCamelCase(JsonObject)->GetObjectField(
				            "data");
			            ReiKey = Data->GetStringField("reikey");
			            RequestSession(OnComplete);
		            }, [OnComplete](int errorCode, FString message)
		            {
			            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
			                                             FString::Format(
				                                             TEXT("Error({0}) {1}"), {errorCode, *message}));
			            OnComplete.ExecuteIfBound(false);
		            });
		return;
	}
#endif

	if (ReiKey.IsEmpty())
	{
		LoadRefreshToken();

		if (!RefreshToken.IsEmpty())
		{
			Refresh([OnComplete](bool bSuccess) { OnComplete.ExecuteIfBound(bSuccess); });
		}
		else
		{
			OnComplete.ExecuteIfBound(false);
		}

		return;
	}

	RequestSession(OnComplete);
}

void UElixirSubsystem::InitializeTimer()
{
	if (const UGameInstance* GameInstance = GetGameInstance())
	{
		TimerManager = &GameInstance->GetTimerManager();
	}
}

void UElixirSubsystem::RequestSession(FCallback OnComplete)
{
	MakeRequest(
		FString::Format(TEXT("/sdk/auth/v2/session/reikey/{0}"), {ReiKey}), nullptr,
		[this, OnComplete](TSharedPtr<FJsonObject> JsonObject)
		{
			const TSharedPtr<FJsonObject> data = ConvertSnakeCaseToCamelCase(JsonObject)->GetObjectField("data");
			RefreshToken = data->GetStringField("refreshToken");
			this->SaveRefreshToken();
			Token = data->GetStringField("token");
			const float ms = data->GetIntegerField("tokenLifeMS") / 1000.0f - 3.f;
			TimerManager->SetTimer(SessionTimerHandle, SessionTimerCallback, ms, false);
			OnComplete.ExecuteIfBound(true);
		},
		[OnComplete](int errorCode, FString message)
		{
			OnComplete.ExecuteIfBound(false);
		});
}

void UElixirSubsystem::GetUserData(FUserDataCallback OnComplete)
{
	MakeRequest(TEXT("/sdk/v2/userinfo/"), nullptr, [this, OnComplete](TSharedPtr<FJsonObject> JsonObject)
	            {
		            const TSharedPtr<FJsonObject> data = ConvertSnakeCaseToCamelCase(JsonObject)->
			            GetObjectField("data");
		            FElixirUserData userData;
		            FJsonObjectConverter::JsonObjectToUStruct(data.ToSharedRef(), &userData, 0, 0, false);
		            OnComplete.ExecuteIfBound(true, userData);
	            },
	            [OnComplete](int errorCode, FString message)
	            {
		            const FElixirUserData userData;
		            OnComplete.ExecuteIfBound(false, userData);
	            });
}

void UElixirSubsystem::Logout(FCallback OnComplete)
{
	ClearRefreshToken();
	Token = "";
	OnComplete.ExecuteIfBound(true);
}

void UElixirSubsystem::GetCollections(FCollectionsCallback OnComplete)
{
	MakeRequest(TEXT("/sdk/v2/nfts/user"), nullptr, [this, OnComplete](TSharedPtr<FJsonObject> JsonObject)
	            {
		            TArray<FElixirCollection> collections;
		            FJsonObjectConverter::JsonArrayToUStruct(
			            ConvertSnakeCaseToCamelCase(JsonObject)->GetArrayField("data"), &collections, 0, 0,
			            false);
		            OnComplete.ExecuteIfBound(true, collections);
	            },
	            [OnComplete](int errorCode, FString message)
	            {
		            const TArray<FElixirCollection> collections;
		            OnComplete.ExecuteIfBound(false, collections);
	            });
}


void UElixirSubsystem::CloseElixir(FCallback OnComplete)
{
	TimerManager->ClearTimer(SessionTimerHandle);
	MakeRequest(FString::Format(TEXT("/sdk/auth/v2/session/closerei/{0}"), {ReiKey}), nullptr,
	            [this, OnComplete](TSharedPtr<FJsonObject> JsonObject)
	            {
		            OnComplete.ExecuteIfBound(true);
	            },
	            [OnComplete](int errorCode, FString message)
	            {
		            OnComplete.ExecuteIfBound(false);
	            });
}

void UElixirSubsystem::Refresh(TFunction<void(bool bSuccess)> OnComplete)
{
	LoadRefreshToken();

	const TSharedPtr<FJsonObject> body = MakeShareable(new FJsonObject());
	body->SetStringField("refreshToken", RefreshToken);
	body->SetStringField("ReiKey", ReiKey);

	MakeRequest(
		TEXT("/sdk/auth/v2/session/refresh"),
		body,
		[this, OnComplete](TSharedPtr<FJsonObject> JsonObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("Refreshed Token"));
			const TSharedPtr<FJsonObject> data = ConvertSnakeCaseToCamelCase(JsonObject)->GetObjectField("data");
			RefreshToken = data->GetStringField("refreshToken");
			SaveRefreshToken();
			Token = data->GetStringField("token");
			const float ms = data->GetIntegerField("tokenLifeMS") / 1000.0f - 3.f;
			TimerManager->SetTimer(SessionTimerHandle, SessionTimerCallback, ms, false);
			OnComplete(true);
		},
		[this, OnComplete](int errorCode, FString message)
		{
			OnComplete(false);
			ClearRefreshToken();
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
			                                 FString::Format(
				                                 TEXT("Error({0}) token renovation {1}"), {errorCode, message}));
		});
}

void UElixirSubsystem::QrVerify(const FString& QrValue, FCallback OnComplete)
{
	const TSharedPtr<FJsonObject> body = MakeShareable(new FJsonObject());
	body->SetStringField("qrValue", QrValue);

	TimerManager->ClearTimer(SessionTimerHandle);
	MakeRequest(TEXT("/sdk/auth/v2/signin/qr-verify"),
	            body,
	            [this, OnComplete](TSharedPtr<FJsonObject> JsonObject)
	            {
		            const TSharedPtr<FJsonObject> data = ConvertSnakeCaseToCamelCase(JsonObject)->
			            GetObjectField("data");
		            RefreshToken = data->GetStringField("refreshToken");
		            this->SaveRefreshToken();
		            Token = data->GetStringField("token");
		            const float ms = data->GetIntegerField("tokenLifeMS") / 1000.0f - 3.f;
		            TimerManager->SetTimer(SessionTimerHandle, SessionTimerCallback, ms, false);
		            OnComplete.ExecuteIfBound(true);
	            },
	            [OnComplete](int errorCode, FString message)
	            {
		            OnComplete.ExecuteIfBound(false);
	            });
}


void UElixirSubsystem::SaveRefreshToken()
{
	if (UElixirSaveData* SaveDataInstance = Cast<UElixirSaveData>(
		UGameplayStatics::CreateSaveGameObject(UElixirSaveData::StaticClass())))
	{
		SaveDataInstance->RefreshToken = RefreshToken;
		if (!UGameplayStatics::SaveGameToSlot(SaveDataInstance, TEXT("Elixir.SaveData"), 0))
			UE_LOG(LogTemp, Error, TEXT("[ELIXIR] Error on save data"));
	}
}

void UElixirSubsystem::ClearRefreshToken()
{
	if (UElixirSaveData* SaveDataInstance = Cast<UElixirSaveData>(
		UGameplayStatics::CreateSaveGameObject(UElixirSaveData::StaticClass())))
	{
		SaveDataInstance->RefreshToken = TEXT("");
		if (!UGameplayStatics::SaveGameToSlot(SaveDataInstance, TEXT("Elixir.SaveData"), 0))
			UE_LOG(LogTemp, Error, TEXT("[ELIXIR] Error on clearing save data"));
	}
}

void UElixirSubsystem::LoadRefreshToken()
{
	if (UElixirSaveData* LoadedDataInstance = Cast<UElixirSaveData>(
		UGameplayStatics::LoadGameFromSlot(TEXT("Elixir.SaveData"), 0)))
	{
		RefreshToken = LoadedDataInstance->RefreshToken;
	}
}

void UElixirSubsystem::MakeRequest(FString uri, TSharedPtr<FJsonObject> body,
                                   TFunction<void(TSharedPtr<FJsonObject> JsonObject)> OnSuccess,
                                   TFunction<void(int errorCode, FString message)> OnError)
{
	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	FString url = BaseURL + uri;
	FString verb;
	if (!body)
	{
		verb = "GET";
	}
	else
	{
		verb = "POST";
		FString bodyString;
		const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&bodyString);
		FJsonSerializer::Serialize(body.ToSharedRef(), Writer);
		HttpRequest->SetContentAsString(bodyString);
	}
	HttpRequest->SetURL(url);
	HttpRequest->SetVerb(verb);
	HttpRequest->SetHeader("content-type", TEXT("application/json"));
	HttpRequest->SetHeader("x-api-key", ApiKey);
	if (!Token.IsEmpty())
	{
		HttpRequest->SetHeader("authorization", FString::Format(TEXT("Bearer {0}"), {Token}));
	}
#if !UE_BUILD_SHIPPING
	UE_LOG(LogTemp, Display, TEXT("[ELIXIR] %s Request: URL(%s)"), *verb, *url);
#endif
	HttpRequest->OnProcessRequestComplete().BindLambda(
		[this, OnSuccess, OnError, url](const FHttpRequestPtr& Request, const FHttpResponsePtr& Response,
		                                const bool bSuccess)
		{
			TSharedPtr<FJsonObject> JsonObject;
			if (bSuccess)
			{
				const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
				if (FJsonSerializer::Deserialize(Reader, JsonObject))
				{
					if (ConvertSnakeCaseToCamelCase(JsonObject)->HasField("error"))
					{
						// Hay que controlar los errores por limite de satoshis.
						UE_LOG(LogTemp, Display, TEXT("[ELIXIR] Error on request (%s): %s"), *url,
						       *Response->GetContentAsString());
						const TSharedPtr<FJsonObject> errorObject = ConvertSnakeCaseToCamelCase(JsonObject)->
							GetObjectField("error");
						const int errorCode = FCString::Atoi(*errorObject->GetStringField("code"));
						const FString errorMessage = errorObject->GetStringField("message");
						OnError(errorCode, errorMessage);
						return;
					}
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("[ELIXIR] Error JSON deserialization (%s): %s"), *url,
					       *Response->GetContentAsString());
					OnError(-2, TEXT("JSON deserialization error."));
					return;
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("[ELIXIR] HTTP generic error (%s)"), *url);
				OnError(-1, TEXT("HTTP generic error."));
				return;
			}
#if !UE_BUILD_SHIPPING
			UE_LOG(LogTemp, Display, TEXT("[ELIXIR] OnSuccess (%s): %s"), *url, *Response->GetContentAsString());
#endif
			OnSuccess(JsonObject);
		});
	HttpRequest->ProcessRequest();
}

FString UElixirSubsystem::GetCurrentToken()
{
	return Token;
}

UElixirSubsystem* UElixirSubsystem::Instance = nullptr;

UElixirSubsystem* UElixirSubsystem::GetInstance()
{
	if (!Instance)
	{
		UE_LOG(LogTemp, Error, TEXT("UElixirSubsystem is not initialized"));
	}

	return Instance;
}
