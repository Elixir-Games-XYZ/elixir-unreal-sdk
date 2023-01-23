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

void InternalElixirController::PrepareElixir(FString _APIKey) {
	REIKey = "";
	FParse::Value(FCommandLine::Get(), TEXT("-rei"), REIKey);
	APIKey = _APIKey;
	BaseURL = "https://kend.elixir.app";
//	BaseURL = "https://sandbox.elixir.app";

}

void InternalElixirController::InitElixir(UObject *WorldContextObject, FCallback OnComplete) {
	// Refreshing Token Lamda.
	SessionTimerCallback.BindLambda([this, WorldContextObject] { 
		Refresh(WorldContextObject, [this](bool res) { UE_LOG(LogTemp, Warning, TEXT("RefreshToken")); }); 
	});
	// Ask for a reikey, devenv only.
	if (REIKey.IsEmpty()) {
		MakeRequest( TEXT("/sdk/auth/v2/dev/reikey"), "", [this, WorldContextObject, OnComplete](TSharedPtr<FJsonObject> JsonObject) {
			TSharedPtr<FJsonObject> data =  JsonObject->GetObjectField("data");
			REIKey = data->GetStringField("reikey");
			RequestSession(WorldContextObject, OnComplete); 
		}, [OnComplete](int errorCode, FString message) {
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Format(TEXT("Error({0}) {1}"), {errorCode, message}));
			OnComplete.ExecuteIfBound(false);
		});
		return;
	}

	if (REIKey.IsEmpty()) {
		OnComplete.ExecuteIfBound(false);
		return;
	}
	RequestSession(WorldContextObject, OnComplete);
}

void InternalElixirController::RequestSession(UObject *WorldContextObject, FCallback OnComplete) {
	MakeRequest(
		FString::Format(TEXT("/sdk/auth/v2/session/reikey/{0}"), {REIKey}), "", [this, WorldContextObject, OnComplete](TSharedPtr<FJsonObject> JsonObject) {
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
	MakeRequest( TEXT("/sdk/v2/userinfo/"), "", [this, OnComplete](TSharedPtr<FJsonObject> JsonObject) {
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
	MakeRequest( TEXT("/sdk/v2/nfts/user"), "", [this, OnComplete](TSharedPtr<FJsonObject> JsonObject) {
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
	MakeRequest( FString::Format(TEXT("/sdk/auth/v2/session/closerei/{0}"), {REIKey}), "", [this, OnComplete](TSharedPtr<FJsonObject> JsonObject) { 
		OnComplete.ExecuteIfBound(true); 
	},
	[OnComplete](int errorCode, FString message) {
		OnComplete.ExecuteIfBound(false);
	});
}
void InternalElixirController::Refresh(UObject *WorldContextObject, TFunction<void(bool result)> OnComplete) {
	LoadRefreshToken();
	MakeRequest( TEXT("/sdk/auth/v2/session/refresh"), FString::Format(TEXT("{\"refreshToken\":\"{0}\", \"reikey\":\"{1}\" }"), {RefreshToken, REIKey}), [this, WorldContextObject, OnComplete](TSharedPtr<FJsonObject> JsonObject) {
		UE_LOG(LogTemp, Warning, TEXT("Refreshed Token"));
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
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	FString url = BaseURL + uri;
	FString verb;
	if (body.IsEmpty()) {
		verb = "GET";
	}
	else
	{
		verb = "POST";
		HttpRequest->SetContentAsString(body);
	}
	HttpRequest->SetURL(url);
	HttpRequest->SetVerb(verb);
	HttpRequest->SetHeader("content-type", TEXT("application/json"));
	HttpRequest->SetHeader("x-api-key", APIKey);
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

FString InternalElixirController::GetCurrentToken(){
	return Token;
}

InternalElixirController *InternalElixirController::_Instance;