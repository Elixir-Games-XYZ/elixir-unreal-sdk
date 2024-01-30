#pragma once

#include "CoreMinimal.h"
#include "ElixirSubsystem.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ElixirController.generated.h"

class UElixirSubsystem;

UCLASS()
class ELIXIR_API UElixirController : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

protected:
public:
	UFUNCTION(BlueprintCallable, Category = "Elixir")
	static void PrepareElixir(FString ApiKey);

	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (AutoCreateRefTerm = "OnComplete"))
	static void InitElixir(const FCallback& OnComplete);

	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (AutoCreateRefTerm = "OnComplete"))
	static void GetUserData(const FUserDataCallback& OnComplete);

	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (AutoCreateRefTerm = "OnComplete"))
	static void Logout(const FCallback& OnComplete);

	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (AutoCreateRefTerm = "OnComplete"))
	static void GetCollections(const FCollectionsCallback& OnComplete);

	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (AutoCreateRefTerm = "OnComplete"))
	static void CloseElixir(const FCallback& OnComplete);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Elixir")
	static FString GetCurrentToken();

	UFUNCTION(BlueprintCallable, Category = "Elixir", meta = (AutoCreateRefTerm = "OnComplete"))
	static void QrVerify(FString QrValue, const FCallback& OnComplete);

private:
	static UGameInstance* GetGameInstanceFromWorld(UWorld* World);
	static UElixirSubsystem* GetElixirSubsystem(UWorld* World);
};
