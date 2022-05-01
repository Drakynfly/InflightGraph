// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

using UnrealBuildTool;

public class InflightGraphExample : ModuleRules
{
	public InflightGraphExample (ReadOnlyTargetRules Target) : base(Target)
    {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = false;

		PublicDependencyModuleNames.AddRange(
			new []
			{
				"Core",
				"CoreUObject",
                "Engine",
                "InflightGraph",
                "InputCore",
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