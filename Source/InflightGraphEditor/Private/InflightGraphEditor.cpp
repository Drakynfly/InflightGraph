// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraphEditor.h"
#include "AssetTypeActions_InflightGraph.h"

DEFINE_LOG_CATEGORY(LogInflightGraphEditor)

#define LOCTEXT_NAMESPACE "Editor_InflightGraph"

IMPLEMENT_MODULE(FInflightGraphEditor, InflightGraphEditor)

FInflightGraphEditor::FInflightGraphEditor()
{
}

void FInflightGraphEditor::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	const EAssetTypeCategories::Type InflightGraphAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(
		FName(TEXT("InflightGraph")), LOCTEXT("InflightGraphAssetCategory", "InflightGraph"));

	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_InflightGraph(InflightGraphAssetCategoryBit)));
}


void FInflightGraphEditor::ShutdownModule()
{
	// Unregister all the asset types that we registered
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
		}
	}
}

void FInflightGraphEditor::RegisterAssetTypeAction(IAssetTools& AssetTools, const TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE