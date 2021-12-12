// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "Toolkits/InflightGraphEditorToolkit.h"
#include "PropertyEditorModule.h"
#include "Slate.h"
#include "GraphEditorActions.h"
#include "EdGraphUtilities.h"
#include "Editor.h"
#include "HAL/PlatformApplicationMisc.h"

#include "Graphs/InflightGraph.h"
#include "EditorGraph/InflightEditorGraphSchema.h"
#include "EditorGraph/InflightGraphEditor.h"
#include "EditorGraph/EditorNodes/InflightEditorGraphNode.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Utility/InflightGraph_Log.h"

#define LOCTEXT_NAMESPACE "InflightGraphEditorToolkit"

const FName FInflightGraphEditorToolkit::DetailsTabId(TEXT("InflightGraphEditorToolkitDetailsTabId"));
const FName FInflightGraphEditorToolkit::GraphTabId(TEXT("InflightGraphEditorToolkitGraphTabId"));


FInflightGraphEditorToolkit::FInflightGraphEditorToolkit()
{
	GEditor->OnBlueprintCompiled().AddRaw(this,&FInflightGraphEditorToolkit::BlueprintCompiled);
}

FInflightGraphEditorToolkit::~FInflightGraphEditorToolkit()
{
	GEditor->OnBlueprintCompiled().RemoveAll(this);
}

FGraphPanelSelectionSet FInflightGraphEditorToolkit::GetSelectedNodes() const
{
	return EdGraphEditor->GetSelectedNodes();
}

TSharedRef<SDockTab> FInflightGraphEditorToolkit::HandleTabManagerSpawnTabDetails(const FSpawnTabArgs & Args)
{
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bUpdatesFromSelection = false;
	DetailsViewArgs.bCustomNameAreaLocation = false;
	DetailsViewArgs.bLockable = false;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.NotifyHook = this;

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

	DetailsWidget = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsWidget->SetObject(GraphAsset);

	return SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			DetailsWidget.ToSharedRef()
		];
}

TSharedRef<SDockTab> FInflightGraphEditorToolkit::HandleTabManagerSpawnTabGraph(const FSpawnTabArgs & Args)
{
	if (GraphAsset->EdGraph != nullptr)
	{
		EdGraphEditor = SNew(SGraphEditor)
			.AdditionalCommands(GraphEditorCommands)
			.GraphToEdit(GraphAsset->EdGraph);
	}
	else
	{
		INFLIGHTGRAPH_ERROR("There is no editor graph inside the graph asset.");
	}
	return SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			EdGraphEditor.ToSharedRef()
		];
}

FLinearColor FInflightGraphEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor::Blue;
}

FName FInflightGraphEditorToolkit::GetToolkitFName() const
{
	return FName("Graph Editor");
}

FText FInflightGraphEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Graph Editor");
}

FString FInflightGraphEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "Graph").ToString();
}

void FInflightGraphEditorToolkit::InitGraphAssetEditor(const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost, UInflightGraph* InGraph)
{
	GraphAsset = InGraph;
	if (GraphAsset->EdGraph == nullptr)
	{
		INFLIGHTGRAPH_LOG("Creating a new graph.");
		GraphAsset->EdGraph = CastChecked<UInflightGraphEditor>(FBlueprintEditorUtils::CreateNewGraph(GraphAsset, NAME_None, UInflightGraphEditor::StaticClass(), UInflightEditorGraphSchema::StaticClass()));
		GraphAsset->EdGraph->bAllowDeletion = false;

		//Give the schema a chance to fill out any required nodes (like the results node)
		const UEdGraphSchema* Schema = GraphAsset->EdGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph(*GraphAsset->EdGraph);
	}

	FGenericCommands::Register();
	FGraphEditorCommands::Register();
	BindToolkitCommands();

	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("LayoutName")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(DetailsTabId, ETabState::OpenedTab)
				->SetHideTabWell(true)
				->SetSizeCoefficient(0.15f)
			)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(GraphTabId, ETabState::OpenedTab)
				->SetHideTabWell(true)
				->SetSizeCoefficient(0.85f)
			)
		);

	FAssetEditorToolkit::InitAssetEditor(InMode, InToolkitHost, FName("GraphEditorIdentifier"), Layout, true, true, GraphAsset);
}

void FInflightGraphEditorToolkit::BlueprintCompiled()
{
	UEdGraph* EdGraph = EdGraphEditor->GetCurrentGraph();
	if (UInflightGraphEditor* MyGraph = Cast<UInflightGraphEditor>(EdGraph))
	{
		MyGraph->RefreshNodes();
	}
}

void FInflightGraphEditorToolkit::SaveAsset_Execute()
{
	if (GraphAsset && GraphAsset->EdGraph)
	{
		UInflightGraphEditor* EdGraph = Cast<UInflightGraphEditor>(GraphAsset->EdGraph);
		EdGraph->SaveGraph();
	}
	FAssetEditorToolkit::SaveAsset_Execute();
}

void FInflightGraphEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = TabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("InflightGraphEditorToolkitWorkspaceMenu", "Graph Editor"));
	const TSharedRef<FWorkspaceItem> WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	TabManager->RegisterTabSpawner(DetailsTabId, FOnSpawnTab::CreateSP(this, &FInflightGraphEditorToolkit::HandleTabManagerSpawnTabDetails))
		.SetDisplayName(LOCTEXT("DetailsTab", "Details"))
		.SetGroup(WorkspaceMenuCategoryRef);
	TabManager->RegisterTabSpawner(GraphTabId, FOnSpawnTab::CreateSP(this, &FInflightGraphEditorToolkit::HandleTabManagerSpawnTabGraph))
		.SetDisplayName(LOCTEXT("GraphTab", "Graph Editor"))
		.SetGroup(WorkspaceMenuCategoryRef);

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
}

void FInflightGraphEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(DetailsTabId);
	InTabManager->UnregisterTabSpawner(GraphTabId);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Commands and Bindings
void FInflightGraphEditorToolkit::BindToolkitCommands()
{
	if (!GraphEditorCommands.IsValid())
	{
		GraphEditorCommands = MakeShareable(new FUICommandList());

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().SelectAll,
			FExecuteAction::CreateRaw(this, &FInflightGraphEditorToolkit::OnCommandSelectAllNodes),
			FCanExecuteAction::CreateRaw(this, &FInflightGraphEditorToolkit::CanSelectAllNodes)
		);

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().Cut,
			FExecuteAction::CreateRaw(this, &FInflightGraphEditorToolkit::OnCommandCut),
			FCanExecuteAction::CreateRaw(this, &FInflightGraphEditorToolkit::CanCutNodes)
		);

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().Copy,
			FExecuteAction::CreateRaw(this, &FInflightGraphEditorToolkit::OnCommandCopy),
			FCanExecuteAction::CreateRaw(this, &FInflightGraphEditorToolkit::CanCopyNodes)
		);

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().Paste,
			FExecuteAction::CreateRaw(this, &FInflightGraphEditorToolkit::OnCommandPaste),
			FCanExecuteAction::CreateRaw(this, &FInflightGraphEditorToolkit::CanPasteNodes)
		);

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().Duplicate,
			FExecuteAction::CreateRaw(this, &FInflightGraphEditorToolkit::OnCommandDuplicate),
			FCanExecuteAction::CreateRaw(this, &FInflightGraphEditorToolkit::CanDuplicateNodes)
		);

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().Delete,
			FExecuteAction::CreateRaw(this, &FInflightGraphEditorToolkit::OnCommandDelete),
			FCanExecuteAction::CreateRaw(this, &FInflightGraphEditorToolkit::CanDeleteNodes)
		);

	}
}

void FInflightGraphEditorToolkit::OnCommandSelectAllNodes()
{
	if (EdGraphEditor.IsValid())
	{
		EdGraphEditor->SelectAllNodes();
	}
}

bool FInflightGraphEditorToolkit::CanSelectAllNodes()
{
	return true;
}

void FInflightGraphEditorToolkit::OnCommandCut()
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

bool FInflightGraphEditorToolkit::CanCutNodes()
{
	return true;
}

void FInflightGraphEditorToolkit::OnCommandCopy()
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

bool FInflightGraphEditorToolkit::CanCopyNodes()
{
	return true;
}

void FInflightGraphEditorToolkit::OnCommandPaste()
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
		UInflightEditorGraphNode* Node = Cast<UInflightEditorGraphNode>(*It);
		GraphAsset->AddNode(Node->AssetNode);
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

bool FInflightGraphEditorToolkit::CanPasteNodes()
{
	return true;
}

void FInflightGraphEditorToolkit::OnCommandDuplicate()
{
	OnCommandCopy();
	OnCommandPaste();
}

bool FInflightGraphEditorToolkit::CanDuplicateNodes()
{
	return true;
}

void FInflightGraphEditorToolkit::OnCommandDelete()
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

bool FInflightGraphEditorToolkit::CanDeleteNodes()
{
	return true;
}

// END Commands and binding
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE