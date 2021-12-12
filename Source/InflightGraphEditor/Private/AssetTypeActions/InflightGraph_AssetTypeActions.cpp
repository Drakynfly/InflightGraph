// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "AssetTypeActions/InflightGraph_AssetTypeActions.h"
#include "Modules/ModuleManager.h"
#include "Graphs/InflightGraph.h"
#include "Toolkits/InflightGraphEditorToolkit.h"
#include "Module/InflightEditor.h"

#define LOCTEXT_NAMESPACE "InflightGraph_AssetTypeActions"

FInflightGraph_AssetTypeActions::FInflightGraph_AssetTypeActions()
{
}

FText FInflightGraph_AssetTypeActions::GetName() const
{
	return LOCTEXT("Name", "Inflight Graph");
}

UClass* FInflightGraph_AssetTypeActions::GetSupportedClass() const
{
	return UInflightGraph::StaticClass();
}

FColor FInflightGraph_AssetTypeActions::GetTypeColor() const
{
	return FColor::Emerald;
}

uint32 FInflightGraph_AssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

bool FInflightGraph_AssetTypeActions::HasActions(const TArray<UObject*>& InObjects) const
{
	return false;
}

void FInflightGraph_AssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, const TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	FInflightEditorModule& Helper = FModuleManager::LoadModuleChecked<FInflightEditorModule>("InflightEditor");
	Helper.StartNodeHelper();

	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (auto&& Object = InObjects.CreateConstIterator(); Object; ++Object)
	{
		if (UInflightGraph* const Graph = Cast<UInflightGraph>(*Object))
		{
			const TSharedRef<FInflightGraphEditorToolkit>EditorToolkit = MakeShareable(new FInflightGraphEditorToolkit());
			EditorToolkit->InitGraphAssetEditor(Mode, EditWithinLevelEditor, Graph);
		}
	}
}

#undef LOCTEXT_NAMESPACE