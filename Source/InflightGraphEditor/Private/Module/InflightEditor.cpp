// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "Module/InflightEditor.h"
#include "Modules/ModuleManager.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"

#include "Nodes/InflightGraphNode.h"
#include "AssetTypeActions/InflightGraph_AssetTypeActions.h"
#include "Utility/InflightGraphEditor_ClassHelper.h"

#define LOCTEXT_NAMESPACE "InflightEditorModule"

void FInflightEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	const TSharedRef<IAssetTypeActions> Actions = MakeShareable(new FInflightGraph_AssetTypeActions());
	AssetTools.RegisterAssetTypeActions(Actions);
}

void FInflightEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	NodeHelper.Reset();
}

void FInflightEditorModule::StartNodeHelper()
{
	if (!NodeHelper.IsValid())
	{
		NodeHelper = MakeShareable(new FInflightGraphEditor_ClassHelper(UInflightGraphNode::StaticClass()));
		FInflightGraphEditor_ClassHelper::AddObservedBlueprintClasses(UInflightGraphNode::StaticClass());
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FInflightEditorModule, InflightEditor)