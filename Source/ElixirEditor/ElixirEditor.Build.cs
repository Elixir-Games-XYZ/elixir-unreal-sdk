using System.Collections.Generic;
using UnrealBuildTool;
using System.IO; 

public class ElixirEditor : ModuleRules
{
	public ElixirEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp17;
		
		PublicDependencyModuleNames.AddRange(
			new[]
			{
				"Core"
			}
		);


		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"CoreUObject",
				"Engine"
			}
		);
		
		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"UnrealEd",					
					"InputCore",
					"SlateCore",
					"Slate",
					"Raven"
				}
			);

		}
	}
}