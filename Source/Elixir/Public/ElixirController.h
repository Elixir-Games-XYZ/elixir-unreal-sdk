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
	static void PrepareElixir(FString APIKey);

	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "OnComplete"))
	static void InitElixir(UObject *WorldContextObject, const FCallback &OnComplete);

	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "OnComplete"))
	static void GetUserData(UObject *WorldContextObject, const FUserDataCallback &OnComplete);

	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "OnComplete"))
	static void GetCollections(UObject *WorldContextObject, const FCollectionsCallback &OnComplete);

	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (WorldContext = "WorldContextObject", AutoCreateRefTerm = "OnComplete"))
	static void CloseElixir(UObject *WorldContextObject, const FCallback &OnComplete);

	UFUNCTION(BlueprintCallable, Category = "Elixir")
	static FString GetCurrentToken();

};
