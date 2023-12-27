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
	FString sub; // Elixir Id
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString iss;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	TArray<FString> wallets;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString nickname;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString picture;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString aud;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString status;
};

DECLARE_DYNAMIC_DELEGATE_TwoParams(FUserDataCallback, bool, bSuccess, FElixirUserData, userData);


USTRUCT(BlueprintType, Category = "Elixir")
struct FElixirNftAttribute
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString trait_type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString value;
};

USTRUCT(BlueprintType, Category = "Elixir")
struct FElixirNFT
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString tokenId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString image;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	TArray<FElixirNftAttribute> attributes;
};

USTRUCT(BlueprintType, Category = "Elixir")
struct FElixirCollection
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString collection;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	FString collectionName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Basic)
	TArray<FElixirNFT> nfts;
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

	void PrepareElixir(FString _APIKey);
	void InitElixir(FCallback OnComplete);
	void GetUserData(FUserDataCallback OnComplete);
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
	void LoadRefreshToken();

	static UElixirSubsystem* Instance;

	FString HashSignature(FString signature);
	FString BaseURL;
	FString REIKey;
	FString APIKey;
	FString Token;
	FString RefreshToken;

	FTimerManager* TimerManager;
	FTimerDelegate SessionTimerCallback;
	FTimerHandle SessionTimerHandle;
};
