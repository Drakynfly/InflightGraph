// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "Nodes/InflightStartNode.h"

#include "Nodes/InflightStateNode.h"

#define LOCTEXT_NAMESPACE "InflightStartNode"

UInflightStartNode::UInflightStartNode()
{
	DefaultNodeTitle = LOCTEXT("NodeTitle", "Start");
}

void UInflightStartNode::LinkArgumentNodeAsChild(UInflightGraphNode* Child)
{
	if (UInflightStateNode* StateNode = Cast<UInflightStateNode>(Child))
	{
		Super::LinkArgumentNodeAsChild(Child);
		ConnectedState = StateNode;
	}
}

#undef LOCTEXT_NAMESPACE