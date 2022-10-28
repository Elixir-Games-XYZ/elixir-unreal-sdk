#include "ElixirController.h"

void UElixirController::PrepareElixir(FString GameID, FString DevAPIKey, FString ProdAPIKey)
{
#if !UE_BUILD_SHIPPING
	InternalElixirController::Instance()->PrepareElixir(DevAPIKey, GameID);
#else
	InternalElixirController::Instance()->PrepareElixir(ProdAPIKey, GameID);
#endif
}

void UElixirController::InitElixir(UObject* WorldContextObject, const FCallback& OnComplete)
{
//		InternalElixirController::Instance()->Refresh(WorldContextObject, [WorldContextObject, OnComplete](bool res) {
//			if (!res)
	InternalElixirController::Instance()->InitElixir(WorldContextObject, OnComplete);
//			else
//				OnComplete.ExecuteIfBound(true); });
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

FString UElixirController::GetToken()
{
	return InternalElixirController::Instance()->GetToken();
}
