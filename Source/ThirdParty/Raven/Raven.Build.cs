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
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib/Linux/libraven_static.a"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib/Linux/libplibsysstatic.a"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Mac)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib/Mac/libraven_static.a"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib/Mac/libplibsysstatic.a"));
		}
		else if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib/Win64/raven_static.lib"));
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib/Win64/plibsysstatic.lib"));
		}
	}
}
