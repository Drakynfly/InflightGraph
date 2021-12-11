// Some copyright should be here...

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
				"Core"
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