// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "EditorGraph/InflightEditorGraphSchema.h"
#include "Module/InflightEditor.h"
#include "Graphs/InflightGraph.h"
#include "EditorGraph/InflightGraphEditorConnectionDrawingPolicy.h"
#include "EditorGraph/EditorNodes/InflightEditorStartNode.h"
#include "EditorGraph/SchemaActions/InflightGraphSchemaAction_NewState.h"
#include "Utility/InflightGraphEditor_ClassHelper.h"

#define LOCTEXT_NAMESPACE "InflightEditorGraphSchema"

void UInflightEditorGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	const FText ToolTip = LOCTEXT("NewUInflightEditorGraphSchemaNodeTooltip", "Add a {NodeName} to the graph.");
	const FText MenuDesc = LOCTEXT("NewUInflightEditorGraphSchemaDescription", "{NodeName}");

	FInflightEditorModule& Module = FModuleManager::LoadModuleChecked<FInflightEditorModule>("InflightEditor");
	const TSharedPtr<FInflightGraphEditor_ClassHelper> Helper = Module.GetHelper();

	// Gathering Input Handlers

	TArray<FInflightGraphEditor_ClassData> AllSubClasses;
	FCategorizedGraphActionListBuilder InputHandlers(TEXT("Add Input Handlers"));

	Helper->GatherClasses(UInflightInputHandlerNode::StaticClass(),AllSubClasses);

	for (auto& ClassData : AllSubClasses)
	{
		FFormatNamedArguments Arguments;
		Arguments.Add(TEXT("NodeName"), ClassData.GetClass()->GetDisplayNameText());

		TSharedPtr<FInflightGraphSchemaAction_NewInputHandler> NewNodeAction;

		NewNodeAction = MakeShareable(new FInflightGraphSchemaAction_NewInputHandler(ClassData.GetCategory(),
			FText::Format(MenuDesc, Arguments), FText::Format(ToolTip, Arguments), 0, ClassData.GetClass()));

		InputHandlers.AddAction(NewNodeAction);
	}

	// Gathering Input State Nodes

	AllSubClasses.Empty();
	FCategorizedGraphActionListBuilder InputStates(TEXT("Add State Node"));

    Helper->GatherClasses(UInflightStateNode::StaticClass(),AllSubClasses);

    for (auto& ClassData : AllSubClasses)
    {
    	FFormatNamedArguments Arguments;
    	Arguments.Add(TEXT("NodeName"), ClassData.GetClass()->GetDisplayNameText());

        TSharedPtr<FInflightGraphSchemaAction_NewState> NewNodeAction;

        NewNodeAction = MakeShareable(new FInflightGraphSchemaAction_NewState(ClassData.GetCategory(),
            FText::Format(MenuDesc, Arguments), FText::Format(ToolTip, Arguments), 0, ClassData.GetClass()));

        InputStates.AddAction(NewNodeAction);
    }

	ContextMenuBuilder.Append(InputHandlers);
	ContextMenuBuilder.Append(InputStates);
}

const FPinConnectionResponse UInflightEditorGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	if(!(A && B))
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Both pins must be available."));

	if (A->GetOwningNode() == B->GetOwningNode())
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("You can't connect a node to itself."));

	if (A->Direction == EGPD_Input && B->Direction == EGPD_Input)
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("You can't connect an input pin to another input pin."));

	if (A->Direction == EGPD_Output && B->Direction == EGPD_Output)
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("You can't connect an output pin to another output pin"));

	UInflightEditorGraphNode* ANode = Cast<UInflightEditorGraphNode>(A->GetOwningNode());
	UInflightEditorGraphNode* BNode = Cast<UInflightEditorGraphNode>(B->GetOwningNode());

	FText ConnectionError;

	if (!ANode->AllowConnection(BNode, B->Direction, ConnectionError))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, ConnectionError);
	}

	if (!BNode->AllowConnection(ANode, A->Direction, ConnectionError))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, ConnectionError);
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

FConnectionDrawingPolicy* UInflightEditorGraphSchema::CreateConnectionDrawingPolicy(const int32 InBackLayerID,
	const int32 InFrontLayerID, const float InZoomFactor, const FSlateRect & InClippingRect,
	FSlateWindowElementList& InDrawElements, UEdGraph* InGraphObj) const
{
	return new FInflightGraphEditorConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
}

void UInflightEditorGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	if (Graph.Nodes.Num() == 0)
	{
		// Create the runtime start node
		// @todo where do the runtime nodes go? if this is a class there is no UInflightGraph yet to put them in
		UInflightGraphBlueprint* GraphAsset = Cast<UInflightGraphBlueprint>(Graph.GetOuter());

		UInflightStartNode* StartingNode = GraphAsset->SpawnNodeInsideGraph<UInflightStartNode>(UInflightStartNode::StaticClass());

		// Create the editor start node
		FGraphNodeCreator<UInflightEditorStartNode> Creator(Graph);
		UInflightEditorStartNode* EdNode = Creator.CreateNode();
		EdNode->AllocateDefaultPins();
		EdNode->NodePosX = 0;
		EdNode->NodePosY = 0;

		// Link the runtime and editor start nodes
		EdNode->SetAssetNode(StartingNode);
		GraphAsset->SetStartNode(StartingNode);

		Creator.Finalize();
	}
}

#undef LOCTEXT_NAMESPACE