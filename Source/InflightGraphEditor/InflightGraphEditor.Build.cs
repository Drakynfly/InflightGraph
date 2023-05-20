// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

using UnrealBuildTool;

public class InflightGraphEditor : ModuleRules
{
	public InflightGraphEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
			new []
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Heart",
                "UnrealEd"
			});

		PrivateDependencyModuleNames.AddRange(
			new []
			{
                "InflightGraph",
                "Slate",
                "InputCore",
                "SlateCore"
			});
    }
}