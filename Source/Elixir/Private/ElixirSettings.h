#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "ElixirSettings.generated.h"

class UObject;

/**
 * General settings for Elixir
 */
UCLASS(config=Game, defaultconfig, meta=(DisplayName="Elixir Settings"))
class UElixirSettings : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()

public:
	UElixirSettings();

	// Override the PlayerId to a custom value for the auth tokens generated in development from rei
	UPROPERTY(config, EditAnywhere, BlueprintReadOnly, Category = "Auth")
	FString PlayerIdOverride;
};
