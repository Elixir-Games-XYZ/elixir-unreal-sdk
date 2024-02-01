using UnrealBuildTool;
using System.IO;

public class Raven : ModuleRules
{
	public Raven(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;
		
		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));
		PublicDefinitions.Add("RAVEN_STATIC_DEFINE");

		if (Target.IsInPlatformGroup(UnrealPlatformGroup.Unix))
		{
			// TODO: platform support
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			// TODO: platform support
		}
		else if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib/raven_static.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib/plibsysstatic.lib"));
		}
	}
}
