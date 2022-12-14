#include "InternalElixirController.h"
#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Runtime/Launch/Resources/Version.h"

#include <string>
#include <sstream>
#include <iomanip>

#define UI UI_ST
THIRD_PARTY_INCLUDES_START
#include <openssl/hmac.h>
THIRD_PARTY_INCLUDES_END
#undef UI
#include "Elixir.h"

void InternalElixirController::PrepareElixir(FString _GameID, FString _DevAPIKey, FString _ProdAPIKey)
{
	REIKey = "";
	FParse::Value(FCommandLine::Get(), TEXT("-rei"), REIKey);

	GameID = _GameID;
#if WITH_EDITOR
	APIKey = _DevAPIKey;
	BaseURL = "https://sandbox.elixir.app";
	SecretKey = "nIhnQDqV6NYN5bYxhFOh4mpOU43fIj6f";
#else
	APIKey = _ProdAPIKey;
	BaseURL = "https://kend.elixir.app";
	SecretKey = "kiu84SHMmIKGjDnIWxH7ICySrcDLB06b";
#endif
}

void InternalElixirController::InitElixir(UObject *WorldContextObject, FCallback OnComplete)
{
#if WITH_EDITOR
	if (REIKey.IsEmpty())
	{
		Token = "eyJhbGciOiJIUzUxMiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI5YmM4MTgzOC00NTY0LTQ4M2UtYmE2MC1iY2JiZjE2YmM1MjQiLCJlbWFpbCI6ImZlcm5hbmRvdGVzdDFAc2F0b3NoaXMuZ2FtZXMiLCJlbnZpcm9ubWVudCI6ImVsaXhpciIsImlhdCI6MTY2ODg1OTI0MiwiZXhwIjoxNzI4ODU5MjQyfQ._S9OJMUaUzkKZRJdiVjeGSzHzqFZhMWIUY3BmZla5etMecSRGFDH6BwRj3zEGygof9pVVZlkrYMiHGpKGcZUxQ";
		MakeRequest( FString::Format(TEXT("/dev/reikey/{0}"), {GameID}), "", [this, WorldContextObject, OnComplete](TSharedPtr<FJsonObject> JsonObject) {
			Token = "";
			REIKey = JsonObject->GetStringField("reikey");
			RequestSession(WorldContextObject, OnComplete); 
		}, [OnComplete](int errorCode, FString message) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Format(TEXT("Error({0}) {1}"), {errorCode, message}));
			OnComplete.ExecuteIfBound(false);
		});
		return;
	}
#endif
	if (REIKey.IsEmpty())
	{
		OnComplete.ExecuteIfBound(false);
		return;
	}
	SessionTimerCallback.BindLambda([this, WorldContextObject] { Refresh(WorldContextObject, [this](bool res) { UE_LOG(LogTemp, Warning, TEXT("RefreshToken")); }); });
	RequestSession(WorldContextObject, OnComplete);
}

void InternalElixirController::RequestSession(UObject *WorldContextObject, FCallback OnComplete) {
	MakeRequest(
		FString::Format(TEXT("/auth/{0}/reikey/{1}"), {GameID, REIKey}), "", [this, WorldContextObject, OnComplete](TSharedPtr<FJsonObject> JsonObject) {
			TSharedPtr<FJsonObject> data =  JsonObject->GetObjectField("data");
			RefreshToken = data->GetStringField("refreshToken");
			this->SaveRefreshToken();
			Token = data->GetStringField("token");
			float ms = (data->GetIntegerField("tokenLifeMS") / 1000.0f) - 3.f;
			GEngine->GetWorldFromContextObjectChecked(WorldContextObject)->GetTimerManager().SetTimer(SessionTimerHandle, SessionTimerCallback, ms, false);
			OnComplete.ExecuteIfBound(true); 
		},
		[OnComplete](int errorCode, FString message) {
			OnComplete.ExecuteIfBound(false);
		});
}

void InternalElixirController::GetUserData(UObject *WorldContextObject, FUserDataCallback OnComplete) {
	MakeRequest( FString::Format(TEXT("/userinfo/game/{0}"), {GameID}), "", [this, OnComplete](TSharedPtr<FJsonObject> JsonObject) {
		TSharedPtr<FJsonObject> data =  JsonObject->GetObjectField("data");
		FElixirUserData userData;
#if ENGINE_MAJOR_VERSION >= 5
		FJsonObjectConverter::JsonObjectToUStruct(data.ToSharedRef(), &userData, 0, 0, false);
#else
		FJsonObjectConverter::JsonObjectToUStruct(data.ToSharedRef(), &userData, 0, 0);
#endif
		OnComplete.ExecuteIfBound(true, userData); 
	},
	[OnComplete](int errorCode, FString message) {
		FElixirUserData userData;
		OnComplete.ExecuteIfBound(false, userData);
	});
}

void InternalElixirController::GetCollections(UObject *WorldContextObject, FCollectionsCallback OnComplete) {
	MakeRequest( FString::Format(TEXT("/nfts/user/{0}"), {GameID}), "", [this, OnComplete](TSharedPtr<FJsonObject> JsonObject) {
		TArray<FElixirCollection> collections;
#if ENGINE_MAJOR_VERSION >= 5
		FJsonObjectConverter::JsonArrayToUStruct(JsonObject->GetArrayField("data"), &collections, 0,0,false);
#else
		FJsonObjectConverter::JsonArrayToUStruct(JsonObject->GetArrayField("data"), &collections, 0, 0);
#endif
		OnComplete.ExecuteIfBound(true, collections); 
	},
	[OnComplete](int errorCode, FString message)
	{
		TArray<FElixirCollection> collections;
		OnComplete.ExecuteIfBound(false, collections);
	});
}


void InternalElixirController::CloseElixir(UObject *WorldContextObject, FCallback OnComplete) {
	GEngine->GetWorldFromContextObjectChecked(WorldContextObject)->GetTimerManager().ClearTimer(SessionTimerHandle);
	MakeRequest( FString::Format(TEXT("/auth/{0}/closerei"), {GameID}), "", [this, OnComplete](TSharedPtr<FJsonObject> JsonObject) { 
		OnComplete.ExecuteIfBound(true); 
	},
	[OnComplete](int errorCode, FString message) {
		OnComplete.ExecuteIfBound(false);
	});
}
void InternalElixirController::Refresh(UObject *WorldContextObject, TFunction<void(bool result)> OnComplete) {
	LoadRefreshToken();
	MakeRequest( TEXT("/auth/refresh-session"), FString::Format(TEXT("{\"refreshToken\":\"{0}\"}"), {*RefreshToken}), [this, WorldContextObject, OnComplete](TSharedPtr<FJsonObject> JsonObject) {
		TSharedPtr<FJsonObject> data =  JsonObject->GetObjectField("data");
		RefreshToken = data->GetStringField("refreshToken");
		SaveRefreshToken();
		Token = data->GetStringField("token");
		float ms = (data->GetIntegerField("tokenLifeMS") / 1000.0f) - 3.f;
		GEngine->GetWorldFromContextObjectChecked(WorldContextObject)->GetTimerManager().SetTimer(SessionTimerHandle, SessionTimerCallback, ms, false);
		OnComplete(true); 
	},
	[OnComplete](int errorCode, FString message) {
		OnComplete(false); 
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Format(TEXT("Error({0}) token renovation {1}"), {errorCode, message}));
	});
}
void InternalElixirController::SaveRefreshToken()
{
	UE_LOG(LogTemp, Display, TEXT("[ELIXIR] Trying to save data"));
	if (UElixirSaveData *SaveDataInstance = Cast<UElixirSaveData>(UGameplayStatics::CreateSaveGameObject(UElixirSaveData::StaticClass()))) {
		SaveDataInstance->RefreshToken = RefreshToken;
		if (!UGameplayStatics::SaveGameToSlot(SaveDataInstance, TEXT("Elixir.SaveData"), 0))
			UE_LOG(LogTemp, Error, TEXT("[ELIXIR] Error on save data"));
	}
}
void InternalElixirController::LoadRefreshToken() {
	if (UElixirSaveData *LoadedDataInstance = Cast<UElixirSaveData>(UGameplayStatics::LoadGameFromSlot(TEXT("Elixir.SaveData"), 0)))
		RefreshToken = LoadedDataInstance->RefreshToken;
}
void InternalElixirController::MakeRequest(FString uri, FString body, TFunction<void(TSharedPtr<FJsonObject> JsonObject)> OnSuccess, TFunction<void(int errorCode, FString message)> OnError)
{
	FTimespan timespan = FDateTime::UtcNow() - FDateTime::MinValue();
	FString timeSpanText = FString::Format(TEXT("{0}"), {(int64)timespan.GetTotalSeconds()});
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	FString url = BaseURL + uri;
	FString signature;
	FString verb;
	if (body.IsEmpty()) {
		verb = "GET";
		signature = FString::Format(TEXT("{0}.\"{1}\""), {timeSpanText, uri});
	}
	else
	{
		verb = "POST";
		HttpRequest->SetContentAsString(body);
		signature = FString::Format(TEXT("{0}.{1}"), {timeSpanText, body});
	}
	HttpRequest->SetURL(url);
	HttpRequest->SetVerb(verb);
	HttpRequest->SetHeader("content-type", TEXT("application/json"));
	HttpRequest->SetHeader("x-api-key", APIKey);
	HttpRequest->SetHeader("x-api-time", timeSpanText);
	HttpRequest->SetHeader("x-api-signature", HashSignature(signature));
	if (!Token.IsEmpty())
		HttpRequest->SetHeader("authorization", "Bearer " + Token);
#if !UE_BUILD_SHIPPING
	UE_LOG(LogTemp, Display, TEXT("[ELIXIR] %s Request: URL(%s)"), *verb, *url);
#endif
	HttpRequest->OnProcessRequestComplete().BindLambda([this, OnSuccess, OnError, url](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
													   {
		TSharedPtr<FJsonObject> JsonObject;
		if (bSuccess) {
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
			if (FJsonSerializer::Deserialize(Reader, JsonObject)) {
				if (JsonObject->HasField("error")) {
					// Hay que controlar los errores por limite de satoshis.
					UE_LOG(LogTemp, Display, TEXT("[ELIXIR] Error on request (%s): %s"), *url, *Response->GetContentAsString());
					TSharedPtr<FJsonObject> errorObject;
					errorObject = JsonObject->GetObjectField("error");
					int errorCode = FCString::Atoi(*errorObject->GetStringField("code"));
					FString errorMessage = errorObject->GetStringField("message");
					OnError(errorCode, errorMessage);
					return;
				}
			}
			else {
				UE_LOG(LogTemp, Error, TEXT("[ELIXIR] Error JSON deserialization (%s): %s"), *url, *Response->GetContentAsString());
				OnError(-2, TEXT("JSON deserialization error."));
				return;
			}
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("[ELIXIR] HTTP generic error (%s)"), *url);
			OnError(-1, TEXT("HTTP generic error."));
			return;
		}
#if !UE_BUILD_SHIPPING
		UE_LOG(LogTemp, Display, TEXT("[ELIXIR] OnSuccess (%s): %s"), *url, *Response->GetContentAsString());
#endif
		OnSuccess(JsonObject); });
	HttpRequest->ProcessRequest();
}

FString InternalElixirController::HashSignature(FString signature)
{
	unsigned char hash[32];
	HMAC_CTX *hmac = HMAC_CTX_new();
	HMAC_CTX_reset(hmac);
	HMAC_Init_ex(hmac, TCHAR_TO_UTF8(*SecretKey), SecretKey.Len(), EVP_sha256(), NULL);
	HMAC_Update(hmac, (unsigned char *)TCHAR_TO_UTF8(*signature), signature.Len());
	unsigned int len = 32;
	HMAC_Final(hmac, hash, &len);
	return BytesToHex(hash, len).ToLower();
}

InternalElixirController *InternalElixirController::_Instance;