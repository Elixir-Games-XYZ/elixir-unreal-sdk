#include "ElixirController.h"

void UElixirController::PrepareElixir(FString GameID, FString DevAPIKey, FString ProdAPIKey)
{
	InternalElixirController::Instance()->PrepareElixir(GameID, DevAPIKey, ProdAPIKey);
}

void UElixirController::InitElixir(UObject* WorldContextObject, const FCallback& OnComplete)
{
	InternalElixirController::Instance()->InitElixir(WorldContextObject, OnComplete);
}

void UElixirController::GetUserData(UObject* WorldContextObject, const FUserDataCallback& OnComplete)
{
	InternalElixirController::Instance()->GetUserData(WorldContextObject, OnComplete);
}

void UElixirController::GetCollections(UObject* WorldContextObject, const FCollectionsCallback& OnComplete)
{
	InternalElixirController::Instance()->GetCollections(WorldContextObject, OnComplete);
}

void UElixirController::CloseElixir(UObject* WorldContextObject, const FCallback& OnComplete)
{
	InternalElixirController::Instance()->CloseElixir(WorldContextObject, OnComplete);
}