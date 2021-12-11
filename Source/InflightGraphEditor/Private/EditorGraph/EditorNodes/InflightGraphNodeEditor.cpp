// Fill out your copyright notice in the Description page of Project Settings.

#include "EditorGraph/EditorNodes/InflightGraphNodeEditor.h"
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

UInflightGraphNodeEditor::UInflightGraphNodeEditor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){}

const FName DefaultPinType("Default");
const FName InPinName("InPin");
const FName OutPinName("OutPin");

TSharedPtr<SGraphNode> UInflightGraphNodeEditor::CreateVisualWidget()
{
	SlateNode= SNew(SInflightGraphNode, this);
	return SlateNode;
}

TSharedPtr<SWidget> UInflightGraphNodeEditor::GetContentWidget()
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

void UInflightGraphNodeEditor::UpdateVisualNode()
{
	SlateNode->UpdateGraphNode();
}

void UInflightGraphNodeEditor::SaveNodesAsChildren(TArray<UEdGraphNode*>& Children)
{
    for (UEdGraphNode* Child : Children)
    {
	    if (const UInflightGraphNodeEditor* Node = Cast<UInflightGraphNodeEditor>(Child))
	    {
		    AssetNode->LinkArgumentNodeAsChild(Node->AssetNode);
	    }
    }
}

bool UInflightGraphNodeEditor::HasOutputPins()
{
	return AssetNode ? AssetNode->HasOutputPins() : true;
}

bool UInflightGraphNodeEditor::HasInputPins()
{
	return AssetNode ? AssetNode->HasInputPins() : true;
}

void UInflightGraphNodeEditor::AllocateDefaultPins()
{
	UEdGraphNode::AllocateDefaultPins();
	if (HasInputPins())
		CreatePin(EGPD_Input, DefaultPinType, InPinName);
	if (HasOutputPins())
		CreatePin(EGPD_Output, DefaultPinType, OutPinName);
}

FText UInflightGraphNodeEditor::GetNodeTitle(const ENodeTitleType::Type TitleType) const
{
    switch (TitleType)
    {
    case ENodeTitleType::Type::MenuTitle:
        return AssetNode->GetNodeTitle();
    default:
        FText Title = GetEdNodeName();
        return Title.IsEmpty() ? AssetNode->GetNodeTitle() : Title;
    }
}

void UInflightGraphNodeEditor::PrepareForCopying()
{
	if (AssetNode)
		AssetNode->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
	UEdGraphNode::PrepareForCopying();
}

void UInflightGraphNodeEditor::DestroyNode()
{
	if (AssetNode)
	{
		AssetNode->GetGraph()->RemoveNode(AssetNode);
		AssetNode->ConditionalBeginDestroy();
		AssetNode = nullptr;
	}
	UEdGraphNode::DestroyNode();
}

void UInflightGraphNodeEditor::AutowireNewNode(UEdGraphPin* FromPin)
{
	if (FromPin)
	{
		UEdGraphNode::AutowireNewNode(FromPin);
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


void UInflightGraphNodeEditor::GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("NodeActionsMenu"), LOCTEXT("NodeActionsMenuHeader", "Node Actions"));
	Section.AddMenuEntry(FGenericCommands::Get().Delete);
	Section.AddMenuEntry(FGenericCommands::Get().Cut);
	Section.AddMenuEntry(FGenericCommands::Get().Copy);
	Section.AddMenuEntry(FGenericCommands::Get().Duplicate);
	Section.AddMenuEntry(FGraphEditorCommands::Get().BreakNodeLinks);
}

void UInflightGraphNodeEditor::SetAssetNode(UInflightGraphNode* InNode)
{
	AssetNode = InNode;
}

UInflightGraphNode* UInflightGraphNodeEditor::GetAssetNode()
{
	return AssetNode;
}

void UInflightGraphNodeEditor::PostCopyNode()
{
	if (AssetNode)
	{
		UEdGraph* EdGraph = GetGraph();
		UObject* ParentAsset = EdGraph ? EdGraph->GetOuter() : nullptr;
		AssetNode->Rename(nullptr, ParentAsset, REN_DontCreateRedirectors | REN_DoNotDirty);
		AssetNode->ClearFlags(RF_Transient);
	}
}

bool UInflightGraphNodeEditor::RenameUniqueNode(const FText & NewName)
{
	bool bRenamedNode = false;

	UInflightGraphEditor* EdGraph = Cast<UInflightGraphEditor>(GetGraph());

	if (EdGraph->IsNameUnique(NewName))
	{
		Modify();
		SetEdNodeName(NewName);
		bRenamedNode = true;
	}
	return bRenamedNode;
}
FText UInflightGraphNodeEditor::GetEdNodeName() const
{
	return EdNodeName;
}
void UInflightGraphNodeEditor::SetEdNodeName(const FText & Name)
{
	EdNodeName = Name;
}

void UInflightGraphNodeEditor::SetEdNodeName(const FName & Name)
{
	SetEdNodeName(FText::FromName(Name));
}


#undef LOCTEXT_NAMESPACE