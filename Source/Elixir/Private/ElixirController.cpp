#include "ElixirController.h"
#include "ElixirSubsystem.h"

void UElixirController::PrepareElixir(FString APIKey)
{
	if (const auto ElixirSubsystem = UElixirSubsystem::GetInstance())
	{
		ElixirSubsystem->PrepareElixir(APIKey);
	}
}

void UElixirController::InitElixir(const FCallback& OnComplete)
{
	if (const auto ElixirSubsystem = UElixirSubsystem::GetInstance())
	{
		ElixirSubsystem->InitElixir(OnComplete);
	}
}

void UElixirController::GetUserData(const FUserDataCallback& OnComplete)
{
	if (const auto ElixirSubsystem = UElixirSubsystem::GetInstance())
	{
		ElixirSubsystem->GetUserData(OnComplete);
	}
}

void UElixirController::GetCollections(const FCollectionsCallback& OnComplete)
{
	if (const auto ElixirSubsystem = UElixirSubsystem::GetInstance())
	{
		ElixirSubsystem->GetCollections(OnComplete);
	}
}

void UElixirController::CloseElixir(const FCallback& OnComplete)
{
	if (const auto ElixirSubsystem = UElixirSubsystem::GetInstance())
	{
		ElixirSubsystem->CloseElixir(OnComplete);
	}
}

FString UElixirController::GetCurrentToken()
{
	if (const auto ElixirSubsystem = UElixirSubsystem::GetInstance())
	{
		return ElixirSubsystem->GetCurrentToken();
	}

	return TEXT("");
}

void UElixirController::QrVerify(FString QrValue, const FCallback& OnComplete)
{
	if (const auto ElixirSubsystem = UElixirSubsystem::GetInstance())
	{
		return ElixirSubsystem->QrVerify(QrValue, OnComplete);
	}
}

UGameInstance* UElixirController::GetGameInstanceFromWorld(UWorld* World)
{
	return World ? World->GetGameInstance() : nullptr;
}

UElixirSubsystem* UElixirController::GetElixirSubsystem(UWorld* World)
{
	const UGameInstance* GameInstance = GetGameInstanceFromWorld(World);
	return GameInstance ? GameInstance->GetSubsystem<UElixirSubsystem>() : nullptr;
}
