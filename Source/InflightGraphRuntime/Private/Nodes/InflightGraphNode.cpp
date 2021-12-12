// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "Nodes/InflightGraphNode.h"
#include "Graphs/InflightGraph.h"

#define LOCTEXT_NAMESPACE "InflightGraphNode"

UInflightGraphNode::UInflightGraphNode()
{
	DefaultNodeTitle = LOCTEXT("Node Title", "Node");
}

UInflightGraphNode* UInflightGraphNode::GetNodePointer_Implementation()
{
	return this;
}

void UInflightGraphNode::SetGraph(UInflightGraph* InGraph)
{
	Graph = InGraph;
}

UInflightGraph* UInflightGraphNode::GetGraph()
{
	return Graph;
}

FText UInflightGraphNode::GetNodeTitle_Implementation()
{
	return DefaultNodeTitle.IsEmpty() ? LOCTEXT("Node Title", "Node") : DefaultNodeTitle;
}

TArray<UInflightGraphNode*> UInflightGraphNode::GetParents()
{
	return ParentNodes;
}

bool UInflightGraphNode::HasParentNodes()
{
	return ParentNodes.Num() > 0;
}

void UInflightGraphNode::LinkArgumentNodeAsChild(UInflightGraphNode* Child)
{
	Child->ParentNodes.Add(this);

	// Children of this node class must override this to save their own list of children.
}

void UInflightGraphNode::ClearLinks()
{
	ParentNodes.Empty();
}

bool UInflightGraphNode::RemoveLinkedNode(UInflightGraphNode* NodeToRemove)
{
	return RemoveNodeFromParents(NodeToRemove) || RemoveNodeFromChildren(NodeToRemove);
}

bool UInflightGraphNode::RemoveNodeFromParents(UInflightGraphNode* NodeToRemove)
{
	return ParentNodes.Remove(NodeToRemove) != 0;
}

bool UInflightGraphNode::RemoveNodeFromChildren(UInflightGraphNode* NodeToRemove)
{
	// Children of this node class must override this to remove from own list of children.
	return false;
}

#undef LOCTEXT_NAMESPACE