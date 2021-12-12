// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "Nodes/InflightStateNode.h"
#include "Graphs/InflightGraph.h"

void UInflightStateNode::Tick(float DeltaTime)
{
	check(Active)
}

void UInflightStateNode::LinkArgumentNodeAsChild(UInflightGraphNode* Child)
{
	if (UInflightInputHandlerNode* InputHandlerNode = Cast<UInflightInputHandlerNode>(Child))
	{
		Super::LinkArgumentNodeAsChild(Child);
		InputStack.Add(InputHandlerNode);
	}
}

bool UInflightStateNode::RemoveNodeFromChildren(UInflightGraphNode* NodeToRemove)
{
	Super::RemoveNodeFromChildren(NodeToRemove);

	if (UInflightInputHandlerNode* InputHandlerNode = Cast<UInflightInputHandlerNode>(NodeToRemove))
	{
		return InputStack.Remove(InputHandlerNode) != 0;
	}

	return false;
}

void UInflightStateNode::ClearLinks()
{
	Super::ClearLinks();
	InputStack.Empty();
}

void UInflightStateNode::SetActive()
{
	if (!Active)
	{
		UE_LOG(LogInflightGraph, Log, TEXT("New State Active: %: "), *GetName())

		Active = true;
		Ticking = NeedsToTick;

		OnBecomeActive();

		for (auto&& InputNode : InputStack)
		{
			InputNode->OnParentActivate(this);
		}
	}
}

void UInflightStateNode::SetInactive()
{
	if (Active)
	{
		Active = false;
		Ticking = false;

		OnBecomeInactive();

		for (auto&& InputNode : InputStack)
		{
			InputNode->OnParentDeactivate();
		}
	}
}

void UInflightStateNode::OnBecomeActive_Implementation()
{
}

void UInflightStateNode::OnBecomeInactive_Implementation()
{
}