// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraphNode.h"

#define LOCTEXT_NAMESPACE "InflightGraphNode"

UInflightGraphEdge* UInflightGraphNode::GetEdge(UInflightGraphNode* ChildNode)
{
	return Edges.Contains(ChildNode) ? Edges.FindChecked(ChildNode) : nullptr;
}

bool UInflightGraphNode::IsLeafNode() const
{
	return ChildrenNodes.Num() == 0;
}

#undef LOCTEXT_NAMESPACE