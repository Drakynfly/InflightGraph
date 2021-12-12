// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "EditorGraph/SchemaActions/InflightGraphSchemaAction_NewState.h"
#include "EditorGraph/EditorNodes/InflightEditorGraphNode.h"
#include "EdGraph/EdGraph.h"
#include "EditorGraph/EditorNodes/InflightEditorInputHandlerNode.h"
#include "Graphs/InflightGraph.h"

#define LOCTEXT_NAMESPACE "InflightEditorGraph_NewNode_SchemaAction"

UEdGraphNode* FInflightGraphSchemaAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin,
                                                                       const FVector2D Location, const bool bSelectNewNode)
{
	check(ParentGraph);

	ParentGraph->Modify();

	UInflightGraph* GraphAsset = CastChecked<UInflightGraph>(ParentGraph->GetOuter());
	GraphAsset->Modify();

	UInflightGraphNode* AssetNode = GraphAsset->SpawnNodeInsideGraph<UInflightGraphNode>(NewNodeClass);

    UInflightEditorGraphNode* EditorNode = CreateEditorNode(ParentGraph, bSelectNewNode, AssetNode);
	EditorNode->BlueprintNode = IsForBlueprintClass;

    //EditorNode->AllocateDefaultPins();   for some reason it was called 2 times even if I only call it here
    EditorNode->AutowireNewNode(FromPin);
    EditorNode->NodePosX = Location.X;
    EditorNode->NodePosY = Location.Y;

	return EditorNode;
}

UInflightEditorGraphNode* FInflightGraphSchemaAction_NewState::CreateEditorNode(UEdGraph* ParentGraph,
																	const bool bSelectNewNode,
																	UInflightGraphNode* AssetNode)
{
    FGraphNodeCreator<UInflightEditorStateNode> Creator(*ParentGraph);
    UInflightEditorStateNode* EdNode = Creator.CreateNode(bSelectNewNode);
    EdNode->SetAssetNode(AssetNode);
    Creator.Finalize();
    return EdNode;
}

UInflightEditorGraphNode* FInflightGraphSchemaAction_NewInputHandler::CreateEditorNode(UEdGraph* ParentGraph,
                                                                               const bool bSelectNewNode,
                                                                               UInflightGraphNode* AssetNode)
{
	FGraphNodeCreator<UInflightEditorInputHandlerNode> Creator(*ParentGraph);
	UInflightEditorInputHandlerNode* EdNode = Creator.CreateNode(bSelectNewNode);
	EdNode->SetAssetNode(AssetNode);
	Creator.Finalize();
	return EdNode;
}

#undef LOCTEXT_NAMESPACE