// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "EditorGraph/InflightEditorGraphSchema.h"
#include "EdGraph/EdGraph.h"

#include "Module/InflightEditor.h"
#include "Graphs/InflightGraph.h"
#include "Nodes/InflightGraphNode.h"
#include "EditorGraph/InflightGraphEditorConnectionDrawingPolicy.h"
#include "EditorGraph/EditorNodes/InflightGraphNodeEditor.h"
#include "EditorGraph/SchemaActions/InflightEditorGraph_NewNode_SchemaAction.h"
#include "Utility/InflightGraphEditor_ClassHelper.h"

#define LOCTEXT_NAMESPACE "InflightEditorGraphSchema"

void UInflightEditorGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{

	FText ToolTip = LOCTEXT("NewUInflightEditorGraphSchemaNodeTooltip", "Add a {NodeName} to the graph.");
	FText MenuDesc = LOCTEXT("NewUInflightEditorGraphSchemaDescription", "{NodeName}");

	FInflightEditorModule& Module = FModuleManager::LoadModuleChecked<FInflightEditorModule>("InflightEditor");
    TSharedPtr<FInflightGraphEditor_ClassHelper> Helper = Module.GetHelper();

	//Gathering C++ classes

	FCategorizedGraphActionListBuilder BaseBuilder(TEXT("C++ Defined Nodes"));

    TArray<FInflightGraphEditor_ClassData> AllSubClasses;
    Helper->GatherClasses(UInflightGraphNode::StaticClass(),AllSubClasses);

    for (auto& NativeClassData : AllSubClasses)
    {
        if (NativeClassData.GetClass()->HasAnyClassFlags(CLASS_Native))
        {
            FFormatNamedArguments Arguments;
            Arguments.Add(TEXT("NodeName"), NativeClassData.GetClass()->GetDisplayNameText());
            TSharedPtr<FInflightEditorGraph_NewNode_SchemaAction> NewNodeAction;

            NewNodeAction = MakeShareable(new FInflightEditorGraph_NewNode_SchemaAction(NativeClassData.GetCategory(), FText::Format(MenuDesc, Arguments), FText::Format(ToolTip, Arguments), 0, NativeClassData.GetClass()));

            BaseBuilder.AddAction(NewNodeAction);
        }
    }

	ContextMenuBuilder.Append(BaseBuilder);

	//Gathering child blueprints
    FCategorizedGraphActionListBuilder BlueprintBuilder(TEXT("Blueprint Defined Nodes"));

	for (auto& BlueprintClassData : AllSubClasses)
	{
		if (!BlueprintClassData.GetClass()->HasAnyClassFlags(CLASS_Native))
		{
			FFormatNamedArguments Arguments;
			Arguments.Add(TEXT("NodeName"), BlueprintClassData.GetClass()->GetDisplayNameText());
            TSharedPtr<FInflightEditorGraph_NewNode_SchemaAction> NewNodeAction;

            NewNodeAction = MakeShareable(new FInflightEditorGraph_NewNode_SchemaAction(BlueprintClassData.GetCategory(), FText::Format(MenuDesc, Arguments), FText::Format(ToolTip, Arguments), 0, BlueprintClassData.GetClass()));

            BlueprintBuilder.AddAction(NewNodeAction);
		}
	}

	ContextMenuBuilder.Append(BlueprintBuilder);
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

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

FConnectionDrawingPolicy* UInflightEditorGraphSchema::CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect & InClippingRect, FSlateWindowElementList & InDrawElements, UEdGraph* InGraphObj) const
{
	return new FInflightGraphEditorConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
}

void UInflightEditorGraphSchema::CreateDefaultNodesForGraph(UEdGraph & Graph) const
{
	if (Graph.Nodes.Num() == 0)
	{
		UInflightGraph* GraphAsset = Cast<UInflightGraph>(Graph.GetOuter());

		GraphAsset->Modify();
		Graph.Modify();

		UInflightGraphNode* AssetNode = GraphAsset->SpawnNodeInsideGraph<UInflightGraphNode>(UInflightGraphNode::StaticClass());

		FGraphNodeCreator<UInflightGraphNodeEditor>Creator(Graph);
		UInflightGraphNodeEditor* EdNode = Creator.CreateNode();
		EdNode->SetAssetNode(AssetNode);
		EdNode->AllocateDefaultPins();

		Creator.Finalize();

		EdNode->NodePosX = 0;
		EdNode->NodePosY = 0;
	}
}
#undef LOCTEXT_NAMESPACE