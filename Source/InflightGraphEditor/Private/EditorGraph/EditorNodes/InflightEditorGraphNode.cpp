// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "EditorGraph/EditorNodes/InflightEditorGraphNode.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "Modules/ModuleManager.h"
#include "Framework/Commands/GenericCommands.h"
#include "ToolMenu.h"
#include "GraphEditorActions.h"
#include "Nodes/InflightGraphNode.h"
#include "Graphs/InflightGraph.h"
#include "EditorGraph/InflightGraphEditor.h"
#include "EditorGraph/SlateWidgets/SInflightGraphNode.h"

#define LOCTEXT_NAMESPACE "InflightGraphNodeEditor"

const FName DefaultPinType("Default");
const FName InPinName("InPin");
const FName OutPinName("OutPin");

UInflightEditorGraphNode::UInflightEditorGraphNode(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer) {}

TSharedPtr<SGraphNode> UInflightEditorGraphNode::CreateVisualWidget()
{
	SlateNode = SNew(SInflightGraphNode, this);
	return SlateNode;
}

TSharedPtr<SWidget> UInflightEditorGraphNode::GetContentWidget()
{
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bAllowSearch = false;
	DetailsViewArgs.bLockable = false;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.DefaultsOnlyVisibility = EEditDefaultsOnlyNodeVisibility::Hide;

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	TSharedPtr<IDetailsView> View = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	View->SetObject(AssetNode);
	return View;
}

void UInflightEditorGraphNode::UpdateVisualNode()
{
	SlateNode->UpdateGraphNode();
}

void UInflightEditorGraphNode::SaveNodesAsChildren(TArray<UEdGraphNode*>& Children)
{
    for (UEdGraphNode* Child : Children)
    {
	    if (const UInflightEditorGraphNode* Node = Cast<UInflightEditorGraphNode>(Child))
	    {
		    AssetNode->LinkArgumentNodeAsChild(Node->AssetNode);
	    }
    }
}

bool UInflightEditorGraphNode::HasOutputPins()
{
	return AssetNode ? AssetNode->HasOutputPins() : true;
}

bool UInflightEditorGraphNode::HasInputPins()
{
	return AssetNode ? AssetNode->HasInputPins() : true;
}

void UInflightEditorGraphNode::AllocateDefaultPins()
{
	Super::AllocateDefaultPins();
	if (HasInputPins())
	{
		CreatePin(EGPD_Input, DefaultPinType, InPinName);
	}
	if (HasOutputPins())
	{
		CreatePin(EGPD_Output, DefaultPinType, OutPinName);
	}
}

FText UInflightEditorGraphNode::GetNodeTitle(const ENodeTitleType::Type TitleType) const
{
    switch (TitleType)
    {
    case ENodeTitleType::Type::MenuTitle:
        return AssetNode->GetNodeTitle();
    default:
        return AssetNode->GetNodeTitle();
    }
}

void UInflightEditorGraphNode::PrepareForCopying()
{
	if (AssetNode)
	{
		AssetNode->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
	}
	Super::PrepareForCopying();
}

void UInflightEditorGraphNode::DestroyNode()
{
	if (AssetNode)
	{
		AssetNode->GetGraph()->RemoveNode(AssetNode);
		AssetNode->ConditionalBeginDestroy();
		AssetNode = nullptr;
	}
	Super::DestroyNode();
}

void UInflightEditorGraphNode::AutowireNewNode(UEdGraphPin* FromPin)
{
	if (FromPin)
	{
		Super::AutowireNewNode(FromPin);
		if (FromPin->Direction == EGPD_Input)
		{
			if (GetSchema()->TryCreateConnection(FromPin, FindPin(OutPinName)))
			{
				FromPin->GetOwningNode()->NodeConnectionListChanged();
			}
		}
		if (FromPin->Direction == EGPD_Output)
		{
			if (GetSchema()->TryCreateConnection(FromPin, FindPin(InPinName)))
			{
				FromPin->GetOwningNode()->NodeConnectionListChanged();
			}
		}
	}
}


void UInflightEditorGraphNode::GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("NodeActionsMenu"), LOCTEXT("NodeActionsMenuHeader", "Node Actions"));

	Section.AddMenuEntry(FGenericCommands::Get().Delete);
	Section.AddMenuEntry(FGenericCommands::Get().Cut);
	Section.AddMenuEntry(FGenericCommands::Get().Copy);
	Section.AddMenuEntry(FGenericCommands::Get().Duplicate);
	Section.AddMenuEntry(FGraphEditorCommands::Get().BreakNodeLinks);
}

void UInflightEditorGraphNode::SetAssetNode(UInflightGraphNode* InNode)
{
	AssetNode = InNode;
}

UInflightGraphNode* UInflightEditorGraphNode::GetAssetNode()
{
	return AssetNode;
}

void UInflightEditorGraphNode::PostCopyNode()
{
	if (AssetNode)
	{
		UEdGraph* EdGraph = GetGraph();
		UObject* ParentAsset = EdGraph ? EdGraph->GetOuter() : nullptr;
		AssetNode->Rename(nullptr, ParentAsset, REN_DontCreateRedirectors | REN_DoNotDirty);
		AssetNode->ClearFlags(RF_Transient);
	}
}

#undef LOCTEXT_NAMESPACE