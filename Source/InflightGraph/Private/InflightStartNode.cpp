// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightStartNode.h"

void UInflightStartNode::OnActivated_Implementation()
{
	Super::OnActivated_Implementation();

	for (auto&& Node : GetLinkedNodes())
	{
		if (!IsValid(Node)) continue;

		Node->AddActivationTrigger(this);
	}
}
