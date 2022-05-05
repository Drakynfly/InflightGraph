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
	StartNode = NodeA;
	EndNode = NodeB;

	OnSetup();
}

void UInflightLinkBase::Activate()
{
	OnActivated();
}

void UInflightLinkBase::Deactivate()
{
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
}