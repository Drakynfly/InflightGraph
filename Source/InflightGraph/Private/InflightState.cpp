// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightState.h"

#include "InflightGraph.h"
#include "InflightGraphModule.h"
#include "InflightLinkBase.h"

void UInflightState::OnSetup_Implementation()
{
}

void UInflightState::OnTriggered_Implementation()
{
	if (!Graph->SetActiveState(this))
	{
		UE_LOG(LogInflightGraph, Warning, TEXT("State \"%s\" failed to set as active"), *Name)
	}

	EventOnTriggered.Broadcast();
}

void UInflightState::OnActivated_Implementation()
{
	UE_LOG(LogInflightGraph, Log, TEXT("State becoming active: %s"), *Name)

	for (UInflightGraphNodeBase* ChildNode : ChildrenNodes)
	{
		if (IsValid(ChildNode))
		{
			UInflightLinkBase* ChildLink = GetChildLink(ChildNode);

			if (IsValid(ChildLink))
			{
				UE_LOG(LogInflightGraph, Log, TEXT("     Child of state: %s. Link to state: %s"), *ChildNode->GetNodeName(), *ChildLink->GetLinkName())

				ChildLink->Activate();
			}
			else
			{
				UE_LOG(LogInflightGraph, Error, TEXT("     Unable to find child link for node: %s"), *ChildNode->GetNodeName());
			}
		}
		else
		{
			UE_LOG(LogInflightGraph, Error, TEXT("     ChildNode in Children Nodes is invalid!"));
		}
	}

	EventOnActivated.Broadcast();
}

void UInflightState::OnDeactivated_Implementation()
{
	UE_LOG(LogInflightGraph, Log, TEXT("State ending active: %s"), *Name)

	for (auto ChildNode : ChildrenNodes)
	{
		if (IsValid(ChildNode))
		{
			UInflightLinkBase* LinkToChild = GetChildLink(ChildNode);

			if (IsValid(LinkToChild))
			{
				LinkToChild->Deactivate();
			}
		}
	}

	EventOnDeactivated.Broadcast();
}