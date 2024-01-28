using UnrealBuildTool;

public class Elixir : ModuleRules
{
	public Elixir(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp17;
		
		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"HTTP",
				"Json",
				"OpenSSL",
				"JsonUtilities",
				"UMG",
				"DeveloperSettings"
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"Raven"	
			}
		);
	}
}