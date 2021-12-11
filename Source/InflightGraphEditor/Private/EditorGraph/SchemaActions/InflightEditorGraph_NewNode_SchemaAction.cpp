// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "EditorGraph/SchemaActions/InflightEditorGraph_NewNode_SchemaAction.h"
#include "EdGraph/EdGraph.h"

#include "Graphs/InflightGraph.h"
#include "EditorGraph/EditorNodes/InflightGraphNodeEditor.h"

#define LOCTEXT_NAMESPACE "InflightEditorGraph_NewNode_SchemaAction"

UEdGraphNode* FInflightEditorGraph_NewNode_SchemaAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin,
	const FVector2D Location, const bool bSelectNewNode)
{
	check(ParentGraph);

	ParentGraph->Modify();

	UInflightGraph* GraphAsset = CastChecked<UInflightGraph>(ParentGraph->GetOuter());
	GraphAsset->Modify();

	UInflightGraphNode* AssetNode = GraphAsset->SpawnNodeInsideGraph<UInflightGraphNode>(NewNodeClass);

    UEdGraphNode* EditorNode=CreateEditorNode(ParentGraph,bSelectNewNode,AssetNode);

    //EditorNode->AllocateDefaultPins();   for some reason it was called 2 times even if I only call it here
    EditorNode->AutowireNewNode(FromPin);
    EditorNode->NodePosX = Location.X;
    EditorNode->NodePosY = Location.Y;

	return EditorNode;
}
UEdGraphNode* FInflightEditorGraph_NewNode_SchemaAction::CreateEditorNode(UEdGraph* ParentGraph, const bool bSelectNewNode, UInflightGraphNode* AssetNode)
{
    FGraphNodeCreator<UInflightGraphNodeEditor>Creator(*ParentGraph);
    UInflightGraphNodeEditor* EdNode = Creator.CreateNode(bSelectNewNode);
    EdNode->SetAssetNode(AssetNode);
    Creator.Finalize();
    return EdNode;
}
#undef LOCTEXT_NAMESPACE