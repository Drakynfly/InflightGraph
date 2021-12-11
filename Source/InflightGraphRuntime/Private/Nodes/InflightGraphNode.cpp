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

TArray<UInflightGraphNode*> UInflightGraphNode::GetChildren()
{
	TArray<UInflightGraphNode*>ReturnArray;
	for (UInflightGraphNode* Node : ChildNodes)
	{
		if (auto&& Object = Node->GetNodePointer())
		{
			ReturnArray.Add(Object);
		}
	}
	return ReturnArray;
}

TArray<UInflightGraphNode*> UInflightGraphNode::GetParents()
{
	return ParentNodes;
}

bool UInflightGraphNode::HasInputPins_Implementation()
{
	return bHasInputPins;
}

bool UInflightGraphNode::HasOutputPins_Implementation()
{
	return bHasOutputPins;
}

void UInflightGraphNode::AddToChildren(UInflightGraphNode* NewSubNode)
{
	ChildNodes.Add(NewSubNode);
}

void UInflightGraphNode::AddToParent(UInflightGraphNode* NewParentNode)
{
	ParentNodes.Add(NewParentNode);
}

bool UInflightGraphNode::HasParentNodes()
{
	return ParentNodes.Num() > 0;
}

void UInflightGraphNode::LinkArgumentNodeAsChild(UInflightGraphNode* Child)
{
	AddToChildren(Child);
	Child->AddToParent(this);
}

void UInflightGraphNode::ClearLinks()
{
	ParentNodes.Empty();
	ChildNodes.Empty();
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
	return ChildNodes.Remove(NodeToRemove) != 0;
}

#undef LOCTEXT_NAMESPACE