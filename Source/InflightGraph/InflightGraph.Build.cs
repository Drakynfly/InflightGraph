// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

using UnrealBuildTool;

public class InflightGraph : ModuleRules
{
	public InflightGraph(ReadOnlyTargetRules Target) : base(Target)
    {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new []
			{
				"Core",
				"CoreUObject",
                "Engine",
                "EnhancedInput"
			});

		PrivateDependencyModuleNames.AddRange(
			new []
			{
                "Slate",
                "SlateCore"
            });
    }
}