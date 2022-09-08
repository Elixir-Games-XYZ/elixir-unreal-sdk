#pragma once

#include "CoreMinimal.h"
#include "InternalElixirController.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ElixirController.generated.h"

UCLASS()
class UElixirController : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
protected:
public:
	UFUNCTION(BlueprintCallable, Category = "Elixir")
	static void PrepareElixir(FString DevAPIKey, FString DevGameID, FString ProdAPIKey, FString ProdGameID) {
#if !UE_BUILD_SHIPPING
		InternalElixirController::Instance()->PrepareElixir(DevAPIKey, DevGameID);
#else
		InternalElixirController::Instance()->PrepareElixir(ProdAPIKey, ProdGameID);
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
};
