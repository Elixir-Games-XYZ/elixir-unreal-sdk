#include "ElixirSubsystem.h"
#include "Elixir.h"
#include "ElixirSettings.h"
#include "Utils.h"

#if PLATFORM_DESKTOP
#include "OverlayMessage.h"
using namespace elixir::overlay::message;
#endif

#include "JsonObjectConverter.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Engine/Engine.h"
#include "Runtime/Launch/Resources/Version.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Containers/Ticker.h"

UElixirSubsystem* UElixirSubsystem::Instance = nullptr;

UElixirSubsystem::UElixirSubsystem()
{
	bOverlayMessagingInitialized = false;
#if PLATFORM_DESKTOP
	EventBufferGameSdk = nullptr;
#endif
}

UElixirSubsystem* UElixirSubsystem::GetInstance()
{
	if (!Instance)
	{
		UE_LOG(LogElixir, Error, TEXT("UElixirSubsystem is not initialized"));
	}

	return Instance;
}

void UElixirSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	InitializeTimer();
	InitOverlayMessaging();

	// Register delegate for ticker callback
#if UE_VERSION_OLDER_THAN(5, 2, 0)
	TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(
			FTickerDelegate::CreateUObject(this, &UElixirSubsystem::Tick));
#else
	TickDelegateHandle = FTSTicker::GetCoreTicker().AddTicker(
		FTickerDelegate::CreateUObject(this, &UElixirSubsystem::Tick));
#endif

	Instance = GetWorld()->GetGameInstance()->GetSubsystem<UElixirSubsystem>();

	UE_LOG(LogElixir, Log, TEXT("UElixirSubsystem initialized"));
}

void UElixirSubsystem::Deinitialize()
{
#if UE_VERSION_OLDER_THAN(5, 2, 0)
	FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
#else
	FTSTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
#endif

#if PLATFORM_DESKTOP
	if (EventBufferGameSdk)
	{
		DestroyEventBuffer(EventBufferGameSdk);
		EventBufferGameSdk = nullptr;
	}

	if (EventBufferOverlayUi)
	{
		DestroyEventBuffer(EventBufferOverlayUi);
		EventBufferOverlayUi = nullptr;
	}
#endif
}

void UElixirSubsystem::PrepareElixir(const FString& InApiKey)
{
	ReiKey = "";
	FParse::Value(FCommandLine::Get(), TEXT("-rei"), ReiKey);
	ApiKey = InApiKey;
	BaseURL = GetMutableDefault<UElixirSettings>()->ElixirApiBaseUrl;
}

void UElixirSubsystem::InitElixir(const FCallback& OnComplete)
{
	// This callback will trigger every time the session refresh timer is exhausted
	SessionTimerCallback.BindLambda([this]
	{
		Refresh([this](bool Res) { UE_LOG(LogElixir, Warning, TEXT("RefreshToken")); });
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
		            }, [OnComplete](int ErrorCode, FString Message)
		            {
			            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
			                                             FString::Format(
				                                             TEXT("Error({0}) {1}"), {ErrorCode, *Message}));
			            OnComplete.ExecuteIfBound(false);
		            });
		return;
	}
#endif

	RequestSession(OnComplete);
}

void UElixirSubsystem::InitializeTimer()
{
	if (const UGameInstance* GameInstance = GetGameInstance())
	{
		TimerManager = &GameInstance->GetTimerManager();
	}
}

void UElixirSubsystem::InitOverlayMessaging()
{
#if PLATFORM_DESKTOP
	EventBufferOverlayUi = CreateEventBuffer(GetEventBufferOverlayUi());
	ClearEventBuffer(EventBufferOverlayUi);

	const char* Error = GetEventBufferError(EventBufferOverlayUi);
	if (Error && Error[0] != 0)
	{
		ClearEventBufferError(EventBufferOverlayUi);
		UE_LOG(LogElixir, Error, TEXT("Failed to create an OverlayUi event buffer (error = '%hs')"), Error);
		return;
	}

	EventBufferGameSdk = CreateEventBuffer(GetEventBufferGameSdk());
	ClearEventBuffer(EventBufferGameSdk);

	const char* Error2 = GetEventBufferError(EventBufferGameSdk);
	if (Error2 && Error2[0] != 0)
	{
		ClearEventBufferError(EventBufferGameSdk);
		UE_LOG(LogElixir, Error, TEXT("Failed to create a GameSdk event buffer (error = '%hs')"), Error2);
	}
#endif
}

bool UElixirSubsystem::Tick(float DeltaSeconds)
{
#if PLATFORM_DESKTOP
	if (EventBufferGameSdk)
	{
		const MessageInterop Msg = ListenToEventBuffer(EventBufferGameSdk);

		if (Msg.type != MTEmpty)
			UE_LOG(LogElixir, Verbose, TEXT("Received a message from overlay (\"type\": %d"), Msg.type);

		switch (Msg.type)
		{
		case MTOpenStateChange:
			{
				FOpenStateChangeOverlayMessage OMsg;
				OMsg.IsOpen = Msg.openStateChange.isOpen;
				OpenStateChange.Broadcast(OMsg);
			}
			break;

		case MTCheckoutResult:
			{
				FCheckoutResultOverlayMessage OMsg;
				OMsg.Sku = Msg.checkoutResult.sku;
				OMsg.Success = Msg.checkoutResult.success;
				CheckoutResult.Broadcast(OMsg);
			}
			break;
		}
	}
#endif

	return true;
}

void UElixirSubsystem::RequestSession(const FCallback& OnComplete)
{
	MakeRequest(FString::Format(TEXT("/sdk/auth/v2/session/reikey/{0}"), {ReiKey}), nullptr,
	            [this, OnComplete](TSharedPtr<FJsonObject> JsonObject)
	            {
		            const TSharedPtr<FJsonObject> Data = ConvertSnakeCaseToCamelCase(JsonObject)->
			            GetObjectField("data");
		            RefreshToken = Data->GetStringField("refreshToken");
		            this->SaveRefreshToken();
		            Token = Data->GetStringField("token");
		            const float Ms = Data->GetIntegerField("tokenLifeMS") / 1000.0f - 3.f;
		            TimerManager->SetTimer(SessionTimerHandle, SessionTimerCallback, Ms, false);
		            OnComplete.ExecuteIfBound(true);
	            },
	            [OnComplete](int ErrorCode, FString Message)
	            {
		            OnComplete.ExecuteIfBound(false);
	            });
}

void UElixirSubsystem::Logout(FCallback OnComplete)
{
	ClearRefreshToken();
	Token = "";
	OnComplete.ExecuteIfBound(true);
}

void UElixirSubsystem::GetUserData(const FUserDataCallback& OnComplete)
{
	MakeRequest(TEXT("/sdk/v2/userinfo/"), nullptr, [this, OnComplete](TSharedPtr<FJsonObject> JsonObject)
	            {
		            const TSharedPtr<FJsonObject> Data = ConvertSnakeCaseToCamelCase(JsonObject)->
			            GetObjectField("data");
		            FElixirUserData UserData;
#if ENGINE_MAJOR_VERSION >= 5
		            FJsonObjectConverter::JsonObjectToUStruct(Data.ToSharedRef(), &UserData, 0, 0, false);
#else
            FJsonObjectConverter::JsonObjectToUStruct(Data.ToSharedRef(), &UserData, 0, 0);
#endif
		            OnComplete.ExecuteIfBound(true, UserData);
	            },
	            [OnComplete](int ErrorCode, FString Message)
	            {
		            const FElixirUserData UserData;
		            OnComplete.ExecuteIfBound(false, UserData);
	            });
}

void UElixirSubsystem::GetCollections(const FCollectionsCallback& OnComplete)
{
	MakeRequest(TEXT("/sdk/v2/nfts/user"), nullptr, [this, OnComplete](TSharedPtr<FJsonObject> JsonObject)
	            {
		            TArray<FElixirCollection> Collections;
#if ENGINE_MAJOR_VERSION >= 5
		            FJsonObjectConverter::JsonArrayToUStruct(
			            ConvertSnakeCaseToCamelCase(JsonObject)->GetArrayField("data"), &Collections, 0, 0, false);
#else
            FJsonObjectConverter::JsonArrayToUStruct(
	            ConvertSnakeCaseToCamelCase(JsonObject)->GetArrayField("data"), &Collections, 0, 0);
#endif
		            OnComplete.ExecuteIfBound(true, Collections);
	            },
	            [OnComplete](int ErrorCode, FString Message)
	            {
		            const TArray<FElixirCollection> Collections;
		            OnComplete.ExecuteIfBound(false, Collections);
	            });
}


void UElixirSubsystem::CloseElixir(const FCallback& OnComplete)
{
	TimerManager->ClearTimer(SessionTimerHandle);
	MakeRequest(FString::Format(TEXT("/sdk/auth/v2/session/closerei/{0}"), {ReiKey}), nullptr,
	            [this, OnComplete](TSharedPtr<FJsonObject> JsonObject)
	            {
		            OnComplete.ExecuteIfBound(true);
	            },
	            [OnComplete](int ErrorCode, FString Message)
	            {
		            OnComplete.ExecuteIfBound(false);
	            });
}

void UElixirSubsystem::Refresh(TFunction<void(bool Result)> OnComplete)
{
	LoadRefreshToken();

	const TSharedPtr<FJsonObject> Body = MakeShareable(new FJsonObject());
	Body->SetStringField("refreshToken", RefreshToken);
	Body->SetStringField("ReiKey", ReiKey);

	MakeRequest(TEXT("/sdk/auth/v2/session/refresh"), Body,
	            [this, OnComplete](TSharedPtr<FJsonObject> JsonObject)
	            {
		            UE_LOG(LogElixir, Warning, TEXT("Refreshed Token"));
		            const TSharedPtr<FJsonObject> Data = ConvertSnakeCaseToCamelCase(JsonObject)->
			            GetObjectField("data");
		            RefreshToken = Data->GetStringField("refreshToken");
		            SaveRefreshToken();
		            Token = Data->GetStringField("token");
		            const float Ms = Data->GetIntegerField("tokenLifeMS") / 1000.0f - 3.f;
		            TimerManager->SetTimer(SessionTimerHandle, SessionTimerCallback, Ms, false);
		            OnComplete(true);
	            },
	            [OnComplete](int ErrorCode, FString Message)
	            {
		            OnComplete(false);
		            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red,
		                                             FString::Format(
			                                             TEXT("Error({0}) token renovation {1}"),
			                                             {ErrorCode, Message}));
	            });
}

void UElixirSubsystem::QrVerify(const FString& QrValue, const FCallback& OnComplete)
{
	const TSharedPtr<FJsonObject> Body = MakeShareable(new FJsonObject());
	Body->SetStringField("qrValue", QrValue);

	TimerManager->ClearTimer(SessionTimerHandle);
	MakeRequest(TEXT("/sdk/auth/v2/signin/qr-verify"), Body,
	            [this, OnComplete](TSharedPtr<FJsonObject> JsonObject)
	            {
		            const TSharedPtr<FJsonObject> Data = ConvertSnakeCaseToCamelCase(JsonObject)->
			            GetObjectField("data");
		            RefreshToken = Data->GetStringField("refreshToken");
		            this->SaveRefreshToken();
		            Token = Data->GetStringField("token");
		            const float Ms = Data->GetIntegerField("tokenLifeMS") / 1000.0f - 3.f;
		            TimerManager->SetTimer(SessionTimerHandle, SessionTimerCallback, Ms, false);
		            OnComplete.ExecuteIfBound(true);
	            },
	            [OnComplete](int ErrorCode, FString Message)
	            {
		            OnComplete.ExecuteIfBound(false);
	            });
}

const FString& UElixirSubsystem::GetCurrentToken() const
{
	return Token;
}


void UElixirSubsystem::SaveRefreshToken()
{
	UElixirSaveData* SaveDataInstance = Cast<UElixirSaveData>(
		UGameplayStatics::CreateSaveGameObject(UElixirSaveData::StaticClass()));
	if (SaveDataInstance)
	{
		SaveDataInstance->RefreshToken = RefreshToken;
		if (!UGameplayStatics::SaveGameToSlot(SaveDataInstance, TEXT("Elixir.SaveData"), 0))
		{
			UE_LOG(LogElixir, Error, TEXT("[ELIXIR] Error on save data"));
		}
	}
}

void UElixirSubsystem::LoadRefreshToken()
{
	UElixirSaveData* LoadedDataInstance = Cast<UElixirSaveData>(
		UGameplayStatics::LoadGameFromSlot(TEXT("Elixir.SaveData"), 0));
	if (LoadedDataInstance)
	{
		RefreshToken = LoadedDataInstance->RefreshToken;
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

void UElixirSubsystem::MakeRequest(const FString& Uri, TSharedPtr<FJsonObject> Body,
                                   TFunction<void(TSharedPtr<FJsonObject> JsonObject)> OnSuccess,
                                   TFunction<void(int ErrorCode, FString Message)> OnError)
{
	const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	FString Url = BaseURL + Uri;
	FString Verb;
	if (!Body)
	{
		Verb = "GET";
	}
	else
	{
		Verb = "POST";
		FString BodyString;
		const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyString);
		FJsonSerializer::Serialize(Body.ToSharedRef(), Writer);
		HttpRequest->SetContentAsString(BodyString);
	}
	HttpRequest->SetURL(Url);
	HttpRequest->SetVerb(Verb);
	HttpRequest->SetHeader("content-type", TEXT("application/json"));
	HttpRequest->SetHeader("x-api-key", ApiKey);
	if (!Token.IsEmpty())
	{
		HttpRequest->SetHeader("authorization", FString::Format(TEXT("Bearer {0}"), {Token}));
	}
#if !UE_BUILD_SHIPPING
	UE_LOG(LogElixir, Display, TEXT("%s Request: URL(%s)"), *Verb, *Url);
#endif
	HttpRequest->OnProcessRequestComplete().BindLambda(
		[this, OnSuccess, OnError, Url](const FHttpRequestPtr& Request, const FHttpResponsePtr& Response,
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
						UE_LOG(LogElixir, Display, TEXT("Error on request (%s): %s"), *Url,
						       *Response->GetContentAsString());
						const TSharedPtr<FJsonObject> errorObject = ConvertSnakeCaseToCamelCase(JsonObject)->
							GetObjectField("error");
						const int ErrorCode = FCString::Atoi(*errorObject->GetStringField("code"));
						const FString ErrorMessage = errorObject->GetStringField("message");
						OnError(ErrorCode, ErrorMessage);
						return;
					}
				}
				else
				{
					UE_LOG(LogElixir, Error, TEXT("Error JSON deserialization (%s): %s"), *Url,
					       *Response->GetContentAsString());
					OnError(-2, TEXT("JSON deserialization error."));
					return;
				}
			}
			else
			{
				UE_LOG(LogElixir, Error, TEXT("HTTP generic error (%s)"), *Url);
				OnError(-1, TEXT("HTTP generic error."));
				return;
			}
#if !UE_BUILD_SHIPPING
			UE_LOG(LogElixir, Display, TEXT("OnSuccess (%s): %s"), *Url, *Response->GetContentAsString());
#endif
			OnSuccess(JsonObject);
		});

	HttpRequest->ProcessRequest();
}

bool UElixirSubsystem::Checkout(const FString& Sku)
{
#if PLATFORM_DESKTOP
	if (!EventBufferOverlayUi)
	{
		UE_LOG(LogElixir, Error, TEXT("Checkout failed: event buffer is not created"));
		return false;
	}

	if (Sku.Len() == 0)
	{
		UE_LOG(LogElixir, Error, TEXT("Checkout failed: invalid empty Sku"));
		return false;
	}

	const char* SkuChar = TCHAR_TO_ANSI(*Sku);
	const size_t BytesWritten = WriteToEventBufferCheckout(EventBufferOverlayUi, SkuChar);
	if (BytesWritten == 0)
	{
		UE_LOG(LogElixir, Error, TEXT("Checkout failed: 0 bytes written"));
		return false;
	}

	UE_LOG(LogElixir, Log, TEXT("Checkout (\"Sku\": %s)"), *Sku);

	return true;
#else
	return false;
#endif
}
