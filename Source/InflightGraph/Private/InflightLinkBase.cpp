// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightLinkBase.h"
#include "InflightNodeBase.h"

void UInflightLinkBase::OnActivated_Implementation()
{
	for (auto&& Node : GetLinkedNodes())
	{
		if (!IsValid(Node)) return;

		//Node->AddActivationTrigger(this);
	}
}

void UInflightLinkBase::OnDeactivated_Implementation()
{
	for (auto&& Node : GetLinkedNodes())
	{
		if (!IsValid(Node)) return;

		//Node->RemoveActivationTrigger(this);
	}
}

void UInflightLinkBase::OnTriggered_Implementation()
{
	for (auto&& Node : GetLinkedNodes())
	{
		if (!IsValid(Node)) return;

		Node->AddActivationTrigger(this);
		Node->Trigger();
		Node->RemoveActivationTrigger(this);
	}
}