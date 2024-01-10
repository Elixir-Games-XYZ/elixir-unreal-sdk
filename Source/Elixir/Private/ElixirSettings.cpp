#include "ElixirSettings.h"
#include "UObject/NameTypes.h"
#include "Runtime/Launch/Resources/Version.h"

#if ENGINE_MAJOR_VERSION >= 5
#include UE_INLINE_GENERATED_CPP_BY_NAME(ElixirSettings)
#endif

UElixirSettings::UElixirSettings()
{
	CategoryName = TEXT("Game");
	EnableDeveloperLogin = true;
	ElixirApiBaseUrl = "https://kend.elixir.app";
}
