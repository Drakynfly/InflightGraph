// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "Toolkits/InflightGraphBlueprintEditor.h"
#include "Slate.h"
#include "GraphEditorActions.h"
#include "EdGraphUtilities.h"
#include "Editor.h"
#include "HAL/PlatformApplicationMisc.h"

#include "Graphs/InflightGraph.h"
#include "EditorGraph/InflightGraphEditor.h"
#include "EditorGraph/EditorNodes/InflightEditorGraphNode.h"
#include "Kismet2/BlueprintEditorUtils.h"

#define LOCTEXT_NAMESPACE "InflightGraphEditorToolkit"

const FName FInflightGraphBlueprintEditor::DetailsTabId(TEXT("InflightGraphEditorToolkitDetailsTabId"));
const FName FInflightGraphBlueprintEditor::GraphTabId(TEXT("InflightGraphEditorToolkitGraphTabId"));


FInflightGraphBlueprintEditor::FInflightGraphBlueprintEditor()
{
	GEditor->OnBlueprintCompiled().AddRaw(this, &FInflightGraphBlueprintEditor::BlueprintCompiled);
}

FInflightGraphBlueprintEditor::~FInflightGraphBlueprintEditor()
{
	GEditor->OnBlueprintCompiled().RemoveAll(this);
}

FName FInflightGraphBlueprintEditor::GetToolkitFName() const
{
	return FName("InflightGraphEditor");
}

FText FInflightGraphBlueprintEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Inflight Graph Editor");
}

FText FInflightGraphBlueprintEditor::GetToolkitToolTipText() const
{
	return GetToolTipTextForObject(GetBlueprintObj());
}

FString FInflightGraphBlueprintEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "Inflight Graph Editor").ToString();
}

FLinearColor FInflightGraphBlueprintEditor::GetWorldCentricTabColorScale() const
{
	return FColor::Emerald;
}

FGraphAppearanceInfo FInflightGraphBlueprintEditor::GetGraphAppearance(UEdGraph* InGraph) const
{
	FGraphAppearanceInfo AppearanceInfo = FBlueprintEditor::GetGraphAppearance(InGraph);
	AppearanceInfo.CornerText = LOCTEXT("AppearanceInfoCornerText", "INFLIGHT");
	return AppearanceInfo;
}

void FInflightGraphBlueprintEditor::InitInflightGraphBlueprintEditor(const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost, UInflightGraphBlueprint* InGraph)
{
	InitBlueprintEditor(InMode, InToolkitHost, { InGraph }, false);
}

void FInflightGraphBlueprintEditor::BlueprintCompiled()
{
	//UEdGraph* EdGraph = EdGraphEditor->GetCurrentGraph();
	//if (UInflightGraphEditor* MyGraph = Cast<UInflightGraphEditor>(EdGraph))
	{
	//	MyGraph->RefreshNodes();
	}
}


void FInflightGraphBlueprintEditor::SaveAsset_Execute()
{
	if (GraphBlueprint && GraphBlueprint->InflightEditorGraph)
	{
		UInflightGraphEditor* EdGraph = Cast<UInflightGraphEditor>(GraphBlueprint->InflightEditorGraph);
		EdGraph->SaveGraph();
	}

	FAssetEditorToolkit::SaveAsset_Execute();
}

/**
void FInflightGraphBlueprintEditor::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = TabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("InflightGraphEditorToolkitWorkspaceMenu", "Graph Editor"));
	const TSharedRef<FWorkspaceItem> WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	TabManager->RegisterTabSpawner(DetailsTabId, FOnSpawnTab::CreateSP(this, &FInflightGraphBlueprintEditor::HandleTabManagerSpawnTabDetails))
		.SetDisplayName(LOCTEXT("DetailsTab", "Details"))
		.SetGroup(WorkspaceMenuCategoryRef);
	TabManager->RegisterTabSpawner(GraphTabId, FOnSpawnTab::CreateSP(this, &FInflightGraphBlueprintEditor::HandleTabManagerSpawnTabGraph))
		.SetDisplayName(LOCTEXT("GraphTab", "Graph Editor"))
		.SetGroup(WorkspaceMenuCategoryRef);

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
}

void FInflightGraphBlueprintEditor::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(DetailsTabId);
	InTabManager->UnregisterTabSpawner(GraphTabId);
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Commands and Bindings
void FInflightGraphBlueprintEditor::BindToolkitCommands()
{
	if (!GraphEditorCommands.IsValid())
	{
		GraphEditorCommands = MakeShareable(new FUICommandList());

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().SelectAll,
			FExecuteAction::CreateRaw(this, &FInflightGraphBlueprintEditor::OnCommandSelectAllNodes),
			FCanExecuteAction::CreateRaw(this, &FInflightGraphBlueprintEditor::CanSelectAllNodes)
		);

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().Cut,
			FExecuteAction::CreateRaw(this, &FInflightGraphBlueprintEditor::OnCommandCut),
			FCanExecuteAction::CreateRaw(this, &FInflightGraphBlueprintEditor::CanCutNodes)
		);

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().Copy,
			FExecuteAction::CreateRaw(this, &FInflightGraphBlueprintEditor::OnCommandCopy),
			FCanExecuteAction::CreateRaw(this, &FInflightGraphBlueprintEditor::CanCopyNodes)
		);

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().Paste,
			FExecuteAction::CreateRaw(this, &FInflightGraphBlueprintEditor::OnCommandPaste),
			FCanExecuteAction::CreateRaw(this, &FInflightGraphBlueprintEditor::CanPasteNodes)
		);

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().Duplicate,
			FExecuteAction::CreateRaw(this, &FInflightGraphBlueprintEditor::OnCommandDuplicate),
			FCanExecuteAction::CreateRaw(this, &FInflightGraphBlueprintEditor::CanDuplicateNodes)
		);

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().Delete,
			FExecuteAction::CreateRaw(this, &FInflightGraphBlueprintEditor::OnCommandDelete),
			FCanExecuteAction::CreateRaw(this, &FInflightGraphBlueprintEditor::CanDeleteNodes)
		);

	}
}

void FInflightGraphBlueprintEditor::OnCommandSelectAllNodes()
{
	if (EdGraphEditor.IsValid())
	{
		EdGraphEditor->SelectAllNodes();
	}
}

bool FInflightGraphBlueprintEditor::CanSelectAllNodes()
{
	return true;
}

void FInflightGraphBlueprintEditor::OnCommandCut()
{
	const FScopedTransaction Transaction(FGenericCommands::Get().Cut->GetDescription());

	OnCommandCopy();

	const FGraphPanelSelectionSet OldSelectedNodes = EdGraphEditor->GetSelectedNodes();
	EdGraphEditor->ClearSelectionSet();
	for (FGraphPanelSelectionSet::TConstIterator It(OldSelectedNodes); It; ++It)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*It);
		if (Node && Node->CanDuplicateNode())
		{
			EdGraphEditor->SetNodeSelection(Node, true);
		}
	}

	OnCommandDelete();

	EdGraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator It(OldSelectedNodes); It; ++It)
	{
		if (UEdGraphNode* Node = Cast<UEdGraphNode>(*It))
		{
			EdGraphEditor->SetNodeSelection(Node, true);
		}
	}
}

bool FInflightGraphBlueprintEditor::CanCutNodes()
{
	return true;
}

void FInflightGraphBlueprintEditor::OnCommandCopy()
{
	FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	FString ExportedText;

	for (FGraphPanelSelectionSet::TIterator It(SelectedNodes); It; ++It)
	{
		if (UEdGraphNode* Node = Cast<UEdGraphNode>(*It))
		{
			Node->PrepareForCopying();
		}
		else
		{
			It.RemoveCurrent();
		}
	}

	FEdGraphUtilities::ExportNodesToText(SelectedNodes, ExportedText);
	FPlatformApplicationMisc::ClipboardCopy(*ExportedText);

	for (FGraphPanelSelectionSet::TIterator It(SelectedNodes); It; ++It)
	{
		if (UInflightEditorGraphNode* Node = Cast<UInflightEditorGraphNode>(*It))
		{
			Node->PostCopyNode();
		}
	}
}

bool FInflightGraphBlueprintEditor::CanCopyNodes()
{
	return true;
}

void FInflightGraphBlueprintEditor::OnCommandPaste()
{
	const FScopedTransaction Transaction(FGenericCommands::Get().Paste->GetDescription());

	const FVector2D PasteLocation = EdGraphEditor->GetPasteLocation();

	UEdGraph* EdGraph = EdGraphEditor->GetCurrentGraph();
	EdGraph->Modify();
	EdGraphEditor->ClearSelectionSet();

	FString ExportedText;
	FPlatformApplicationMisc::ClipboardPaste(ExportedText);
	TSet<UEdGraphNode*> ImportedNodes;
	FEdGraphUtilities::ImportNodesFromText(EdGraph, ExportedText, ImportedNodes);

	for (TSet<UEdGraphNode*>::TIterator It(ImportedNodes); It; ++It)
	{
		const UInflightEditorGraphNode* Node = Cast<UInflightEditorGraphNode>(*It);
		GraphBlueprint->AddNode(Node->AssetNode);
	}

	FVector2D AvgNodePosition(0.0f, 0.0f);

	for (TSet<UEdGraphNode*>::TIterator It(ImportedNodes); It; ++It)
	{
		const UEdGraphNode* Node = *It;
		AvgNodePosition.X += Node->NodePosX;
		AvgNodePosition.Y += Node->NodePosY;
	}

	const float InvNumNodes = 1.0f / static_cast<float>(ImportedNodes.Num());
	AvgNodePosition.X *= InvNumNodes;
	AvgNodePosition.Y *= InvNumNodes;

	for (TSet<UEdGraphNode*>::TIterator It(ImportedNodes); It; ++It)
	{
		UEdGraphNode* Node = *It;
		EdGraphEditor->SetNodeSelection(Node, true);

		Node->NodePosX = (Node->NodePosX - AvgNodePosition.X) + PasteLocation.X;
		Node->NodePosY = (Node->NodePosY - AvgNodePosition.Y) + PasteLocation.Y;

		Node->SnapToGrid(16);

		// Give new node a different Guid from the old one
		Node->CreateNewGuid();
	}

	EdGraphEditor->NotifyGraphChanged();

	if (UObject* GraphOwner = EdGraph->GetOuter())
	{
		GraphOwner->PostEditChange();
		// ReSharper disable once CppExpressionWithoutSideEffects
		GraphOwner->MarkPackageDirty();
	}

}

bool FInflightGraphBlueprintEditor::CanPasteNodes()
{
	return true;
}

void FInflightGraphBlueprintEditor::OnCommandDuplicate()
{
	OnCommandCopy();
	OnCommandPaste();
}

bool FInflightGraphBlueprintEditor::CanDuplicateNodes()
{
	return true;
}

void FInflightGraphBlueprintEditor::OnCommandDelete()
{
	const FScopedTransaction Transaction(FGenericCommands::Get().Delete->GetDescription());
	EdGraphEditor->GetCurrentGraph()->Modify();

	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	EdGraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator It(SelectedNodes); It; ++It)
	{
		if (UEdGraphNode* Node = Cast<UEdGraphNode>(*It))
		{
			if (Node->CanUserDeleteNode())
			{
				Node->Modify();
				Node->DestroyNode();
			}
		}
	}
}

bool FInflightGraphBlueprintEditor::CanDeleteNodes()
{
	return true;
}

// END Commands and binding
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE