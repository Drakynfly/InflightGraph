// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "AssetTypeActions/InflightGraph_AssetTypeActions.h"
#include "EditorGraph/InflightGraphEditor.h"
#include "Factories/InflightGraphBlueprintFactory.h"
#include "Graphs/InflightGraph.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Toolkits/InflightGraphBlueprintEditor.h"

#define LOCTEXT_NAMESPACE "InflightGraph_AssetTypeActions"

FInflightGraph_AssetTypeActions::FInflightGraph_AssetTypeActions()
{
}

FText FInflightGraph_AssetTypeActions::GetName() const
{
	return LOCTEXT("Name", "Inflight Graph Blueprint");
}

UClass* FInflightGraph_AssetTypeActions::GetSupportedClass() const
{
	return UInflightGraphBlueprint::StaticClass();
}

FColor FInflightGraph_AssetTypeActions::GetTypeColor() const
{
	return FColor::Emerald;
}

uint32 FInflightGraph_AssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Misc;
}

void FInflightGraph_AssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects,
													  const TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	//Helper.StartNodeHelper();

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		const auto InflightBlueprint = Cast<UInflightGraphBlueprint>(*ObjIt);

		if (InflightBlueprint != nullptr && InflightBlueprint->SkeletonGeneratedClass && InflightBlueprint->GeneratedClass)
		{
			const bool bBringToFrontIfOpen = true;
#if WITH_EDITOR
			if (IAssetEditorInstance* EditorInstance =
				GEditor->GetEditorSubsystem<UAssetEditorSubsystem>()->FindEditorForAsset(InflightBlueprint, bBringToFrontIfOpen))
			{
				EditorInstance->FocusWindow(InflightBlueprint);
			}
			else
#endif
			{
				const TSharedRef<FInflightGraphBlueprintEditor> NewInflightGraphBlueprintEditor(new FInflightGraphBlueprintEditor());
				NewInflightGraphBlueprintEditor->InitInflightGraphBlueprintEditor( Mode, EditWithinLevelEditor, InflightBlueprint);
			}
		}
		else
		{
			FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("FailedToLoadCorruptAnimBlueprint",
				"The Anim Blueprint could not be loaded because it is corrupt."));
		}
	}
}

UFactory* FInflightGraph_AssetTypeActions::GetFactoryForBlueprintType(UBlueprint* InBlueprint) const
{
	const UInflightGraphBlueprint* InflightGraphBlueprint = CastChecked<UInflightGraphBlueprint>(InBlueprint);

	UInflightGraphBlueprintFactory* InflightGraphBlueprintFactory = NewObject<UInflightGraphBlueprintFactory>();
	InflightGraphBlueprintFactory->ParentClass = TSubclassOf<UInflightGraph>(*InflightGraphBlueprint->GeneratedClass);
	return InflightGraphBlueprintFactory;
}

#undef LOCTEXT_NAMESPACE