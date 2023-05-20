// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightNodeBase.h"

#if WITH_EDITOR
void UInflightNodeBase::SetLinkedNodes(TSet<TObjectPtr<UInflightNodeBase>> Nodes)
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

void UInflightNodeBase::Trigger()
{
	if (ensure(Activated))
	{
		OnTriggered();
	}
}

void UInflightNodeBase::Activate()
{
	if (ensure(!Activated))
	{
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
	}
}

void UInflightNodeBase::OnActivated_Implementation()
{
}

void UInflightNodeBase::OnDeactivated_Implementation()
{
}

void UInflightNodeBase::OnTriggered_Implementation()
{
}