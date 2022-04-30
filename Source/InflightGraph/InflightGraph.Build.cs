// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

using UnrealBuildTool;

public class InflightGraph : ModuleRules
{
	public InflightGraph(ReadOnlyTargetRules Target) : base(Target)
    {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = false;

		PublicDependencyModuleNames.AddRange(
			new []
			{
				"Core",
				"CoreUObject",
                "Engine",
			});

		PrivateDependencyModuleNames.AddRange(
			new []
			{
                "Slate",
                "SlateCore",
                "GameplayTags"
            });
    }
}