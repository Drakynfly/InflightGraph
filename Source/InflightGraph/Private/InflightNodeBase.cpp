// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightNodeBase.h"

#include "InflightGraph.h"

UInflightGraph* UInflightNodeBase::GetInflightGraph() const
{
	return GetTypedOuter<UInflightGraph>();
}

#if WITH_EDITOR

void UInflightNodeBase::SetLinkedNodes(const TSet<TObjectPtr<UInflightNodeBase>>& Nodes)
{
	LinkedNodes = Nodes;
}
#endif

bool UInflightNodeBase::IsActive() const
{
	return Activated;
}

TArray<UInflightNodeBase*> UInflightNodeBase::GetLinkedNodes() const
{
	return LinkedNodes.Array();
}

void UInflightNodeBase::AddActivationTrigger(UObject* Trigger)
{
	if (IsValid(Trigger))
	{
		ActivationTriggers.AddUnique(Trigger);

		if (!Activated)
		{
			Activate();
		}
	}
}

void UInflightNodeBase::RemoveActivationTrigger(UObject* Trigger)
{
	if (IsValid(Trigger))
	{
		ActivationTriggers.Remove(Trigger);

		if (ActivationTriggers.IsEmpty())
		{
			Deactivate();
		}
	}
}

void UInflightNodeBase::Trigger(const FInputActionValue& ActionValue)
{
	if (ensure(Activated))
	{
		OnTriggered(ActionValue);
	}
}

void UInflightNodeBase::Activate()
{
	if (ensure(!Activated))
	{
		GetInflightGraph()->MarkNodeActive(this);
		Activated = true;
		OnActivated();
	}
}

void UInflightNodeBase::Deactivate()
{
	if (ensure(Activated))
	{
		OnDeactivated();
		Activated = false;
		GetInflightGraph()->MarkNodeActive(this);
	}
}

void UInflightNodeBase::OnActivated_Implementation()
{
}

void UInflightNodeBase::OnDeactivated_Implementation()
{
}

void UInflightNodeBase::OnTriggered_Implementation(const FInputActionValue& ActionValue)
{
}