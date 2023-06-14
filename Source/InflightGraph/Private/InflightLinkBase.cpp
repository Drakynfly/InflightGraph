// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightLinkBase.h"
#include "InflightNodeBase.h"

void UInflightLinkBase::OnTriggered_Implementation(const FInputActionValue& ActionValue)
{
	for (auto&& Node : GetLinkedNodes())
	{
		if (!IsValid(Node)) return;

		Node->AddActivationTrigger(this);
		Node->Trigger(ActionValue);
		Node->RemoveActivationTrigger(this);
	}
}