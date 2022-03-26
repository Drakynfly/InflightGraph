// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

using UnrealBuildTool;

public class InflightEditor : ModuleRules
{
	public InflightEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = false;

		PublicDependencyModuleNames.AddRange(
			new []
			{
				"Core",
				"Kismet",
				"AssetTools"
			});

		PrivateDependencyModuleNames.AddRange(
			new []
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "EditorStyle",
                "UnrealEd",
                "AssetTools",
                "GraphEditor",
                "ApplicationCore",
				"ToolMenus",
				"InflightGraphRuntime"
			});
	}
}