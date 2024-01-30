#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "TimerManager.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/SaveGame.h"
#include "ElixirSubsystem.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FCallback, bool, bSuccess);

USTRUCT(BlueprintType, Category = "Elixir")
struct FElixirUserData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Sub; // Elixir Id
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Iss;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	TArray<FString> Wallets;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Nickname;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Picture;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Aud;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Status;
};

DECLARE_DYNAMIC_DELEGATE_TwoParams(FUserDataCallback, bool, bSuccess, FElixirUserData, userData);


USTRUCT(BlueprintType, Category = "Elixir")
struct FElixirNftAttribute
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString TraitType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString DisplayType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Value;
};

USTRUCT(BlueprintType, Category = "Elixir")
struct FElixirNft
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString TokenId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Image;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	TArray<FElixirNftAttribute> Attributes;
};

USTRUCT(BlueprintType, Category = "Elixir")
struct FElixirCollection
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString Collection;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString CollectionName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	TArray<FElixirNft> Nfts;
};

DECLARE_DYNAMIC_DELEGATE_TwoParams(FCollectionsCallback, bool, bSuccess, const TArray<FElixirCollection> &,
                                   collections);

UCLASS()
class UElixirSaveData : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString RefreshToken;
};

UCLASS()
class UElixirSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	static UElixirSubsystem* GetInstance();

	void PrepareElixir(FString InApiKey);
	void InitElixir(FCallback OnComplete);
	void GetUserData(FUserDataCallback OnComplete);
	void Logout(FCallback OnComplete);
	void GetCollections(FCollectionsCallback OnComplete);
	void CloseElixir(FCallback OnComplete);
	void Refresh(TFunction<void(bool result)> OnComplete);
	void QrVerify(const FString& QrValue, FCallback OnComplete);
	FString GetCurrentToken();

private:
	void InitializeTimer();
	void RequestSession(FCallback OnComplete);
	void MakeRequest(FString uri, TSharedPtr<FJsonObject> body,
	                 TFunction<void(TSharedPtr<FJsonObject> JsonObject)> OnSuccess,
	                 TFunction<void(int errorCode, FString message)> OnError);
	void SaveRefreshToken();
	void ClearRefreshToken();
	void LoadRefreshToken();

	static UElixirSubsystem* Instance;

	FString HashSignature(FString signature);
	FString BaseURL;
	FString ReiKey;
	FString ApiKey;
	FString Token;
	FString RefreshToken;

	FTimerManager* TimerManager;
	FTimerDelegate SessionTimerCallback;
	FTimerHandle SessionTimerHandle;
};
