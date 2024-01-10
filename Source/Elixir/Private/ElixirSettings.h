#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h" 
#include "ElixirSettings.generated.h"

class UObject;

/**
 * General settings for Elixir
 */
UCLASS(config=Game, defaultconfig, meta=(DisplayName="Elixir Settings"))
class UElixirSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UElixirSettings();

	// Override the PlayerId to a custom value for the auth tokens generated in development from rei
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Auth")
	FString PlayerIdOverride;

	// Automatically log in as a developer player ID in development builds
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Auth")
	bool EnableDeveloperLogin;

	// Base URL for the Elixir API. Only override this when instructed by the Elixir team
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Auth")
	FString ElixirApiBaseUrl;
};
