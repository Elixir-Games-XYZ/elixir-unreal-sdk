#pragma once

#include "ElixirTypes.h"
#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "TimerManager.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/SaveGame.h"
#include "Misc/EngineVersionComparison.h"
#include "ElixirSubsystem.generated.h"

#if PLATFORM_DESKTOP
namespace elixir::overlay::message
{
	class EventBufferInterop;
}
#endif


/** TODO: Add a comment */
UCLASS(BlueprintType)
class ELIXIR_API UElixirSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_DELEGATE_OneParam(FCallback, bool, bSuccess);

	DECLARE_DYNAMIC_DELEGATE_TwoParams(FCollectionsCallback, bool, bSuccess, const TArray<FElixirCollection>&,
	                                   Collections);

	DECLARE_DYNAMIC_DELEGATE_TwoParams(FUserDataCallback, bool, bSuccess, FElixirUserData, UserData);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOpenStateChangeMessageDelegate,
	                                            const FOpenStateChangeOverlayMessage&, Message);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCheckoutResultMessageDelegate, const FCheckoutResultOverlayMessage&,
	                                            Message);

public:
	UElixirSubsystem();
	static UElixirSubsystem* GetInstance();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** TODO: Add a comment */
	UFUNCTION(BlueprintCallable, Category = "Elixir")
	void PrepareElixir(const FString& InApiKey);

	/** TODO: Add a comment */
	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (AutoCreateRefTerm = "OnComplete"))
	void InitElixir(const FCallback& OnComplete);

	/** TODO: Add a comment */
	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (AutoCreateRefTerm = "OnComplete"))
	void GetUserData(const FUserDataCallback& OnComplete);

	/** TODO: Add a comment */
	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (AutoCreateRefTerm = "OnComplete"))
	void Logout(FCallback OnComplete);

	/** TODO: Add a comment */
	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (AutoCreateRefTerm = "OnComplete"))
	void GetCollections(const FCollectionsCallback& OnComplete);

	/** TODO: Add a comment */
	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (AutoCreateRefTerm = "OnComplete"))
	void CloseElixir(const FCallback& OnComplete);

	/** TODO: Add a comment */
	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (AutoCreateRefTerm = "OnComplete"))
	void QrVerify(const FString& QrValue, const FCallback& OnComplete);

	/** TODO: Add a comment */
	UFUNCTION(BlueprintCallable, Category = "Elixir")
	const FString& GetCurrentToken() const;

	/** TODO: Add a comment */
	UFUNCTION(BlueprintCallable, Category = "Elixir")
	bool Checkout(const FString& Sku);

	/** TODO: Add a comment */
	void Refresh(TFunction<void(bool Result)> OnComplete);

private:
	void InitializeTimer();
	void InitOverlayMessaging();
	bool Tick(float DeltaSeconds);
	void RequestSession(const FCallback& OnComplete);
	void MakeRequest(const FString& Uri, TSharedPtr<FJsonObject> Body,
	                 TFunction<void(TSharedPtr<FJsonObject> JsonObject)> OnSuccess,
	                 TFunction<void(int ErrorCode, FString Message)> OnError);
	void SaveRefreshToken();
	void LoadRefreshToken();
	void ClearRefreshToken();

private:
	static UElixirSubsystem* Instance;

#if UE_VERSION_OLDER_THAN(5, 2, 0)
	FDelegateHandle TickDelegateHandle;
#else
	FTSTicker::FDelegateHandle TickDelegateHandle;
#endif

	FString BaseURL;
	FString ReiKey;
	FString ApiKey;
	FString Token;
	FString RefreshToken;

	FTimerManager* TimerManager;
	FTimerDelegate SessionTimerCallback;
	FTimerHandle SessionTimerHandle;

	bool bOverlayMessagingInitialized;

#if PLATFORM_DESKTOP
	elixir::overlay::message::EventBufferInterop* EventBufferGameSdk;
	elixir::overlay::message::EventBufferInterop* EventBufferOverlayUi;
#endif

public:
	/** TODO: Add a comment */
	UPROPERTY(BlueprintAssignable)
	FOnOpenStateChangeMessageDelegate OpenStateChange;

	/** TODO: Add a comment */
	UPROPERTY(BlueprintAssignable)
	FOnCheckoutResultMessageDelegate CheckoutResult;
};

UCLASS()
class ELIXIR_API UElixirSaveData : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString RefreshToken;
};
