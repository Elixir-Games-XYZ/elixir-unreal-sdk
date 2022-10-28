#pragma once

#include "CoreMinimal.h"
#include "InternalElixirController.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ElixirController.generated.h"

UCLASS()
class ELIXIR_API UElixirController : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
protected:
public:
	UFUNCTION(BlueprintCallable, Category = "Elixir")
	static void PrepareElixir(FString GameID, FString DevAPIKey, FString ProdAPIKey ) {
#if !UE_BUILD_SHIPPING
		InternalElixirController::Instance()->PrepareElixir(DevAPIKey, GameID);
#else
		InternalElixirController::Instance()->PrepareElixir(ProdAPIKey, GameID);
#endif
	}

	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "OnComplete"))
	static void InitElixir(UObject *WorldContextObject, const FCallback &OnComplete) {
		//		InternalElixirController::Instance()->Refresh(WorldContextObject, [WorldContextObject, OnComplete](bool res) {
		//			if (!res)
		InternalElixirController::Instance()->InitElixir(WorldContextObject, OnComplete);
		//			else
		//				OnComplete.ExecuteIfBound(true); });
	}

	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "OnComplete"))
	static void GetUserData(UObject *WorldContextObject, const FUserDataCallback &OnComplete) {
		InternalElixirController::Instance()->GetUserData(WorldContextObject, OnComplete);
	}

	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "OnComplete"))
	static void GetCollections(UObject *WorldContextObject, const FCollectionsCallback &OnComplete) {
		InternalElixirController::Instance()->GetCollections(WorldContextObject, OnComplete);
	}

	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "OnComplete"))
	static void CloseElixir(UObject *WorldContextObject, const FCallback &OnComplete) {
		InternalElixirController::Instance()->CloseElixir(WorldContextObject, OnComplete);
	}

	UFUNCTION(BlueprintCallable, Category = "Elixir")
	static FString GetToken() {
		return InternalElixirController::Instance()->GetToken();
	}
};
