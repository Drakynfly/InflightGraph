// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightLinkBase.h"
#include "InflightGraph.h"
#include "InflightGraphModule.h"

void UInflightLinkBase::SetName(const FString& InName)
{
	Name = InName;
}

void UInflightLinkBase::Setup(UInflightGraph* InflightGraph, UInflightGraphNodeBase* NodeA,
                              UInflightGraphNodeBase* NodeB)
{
	Graph = InflightGraph;
	StartNodes.AddUnique(NodeA);
	EndNodes.AddUnique(NodeB);

	OnSetup();
}

void UInflightLinkBase::Activate()
{
	for (auto&& EndNode : EndNodes)
	{
		if (IsValid(EndNode))
		{
			EndNode->AddActivationTrigger(this);
		}
	}

	OnActivated();
}

void UInflightLinkBase::Deactivate()
{
	for (auto&& EndNode : EndNodes)
	{
		if (IsValid(EndNode))
		{
			EndNode->RemoveActivationTrigger(this);
		}
	}

	OnDeactivated();
}

void UInflightLinkBase::Trigger()
{
	OnTriggered();
}

void UInflightLinkBase::OnSetup()
{
}

void UInflightLinkBase::OnActivated()
{
}

void UInflightLinkBase::OnDeactivated()
{
}

void UInflightLinkBase::OnTriggered()
{
	for (auto&& EndNode : EndNodes)
	{
		if (IsValid(EndNode))
		{
			EndNode->Trigger();
		}
	}
}