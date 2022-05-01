// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraphNodeBase.h"
#include "InflightGraph.h"
#include "InflightGraphModule.h"

#define LOCTEXT_NAMESPACE "InflightGraphNode"

UInflightGraphLink* UInflightGraphNodeBase::GetLink(UInflightGraphNodeBase* ChildNode)
{
	return Links.Contains(ChildNode) ? Links.FindChecked(ChildNode) : nullptr;
}

bool UInflightGraphNodeBase::IsRootNode() const
{
	return ParentNodes.IsEmpty();
}

bool UInflightGraphNodeBase::IsLeafNode() const
{
	return ChildrenNodes.IsEmpty();
}

void UInflightGraphNodeBase::Setup(UInflightGraph* InGraph, const FString& InName)
{
	Graph = InGraph;
	Name = InName;
	OnSetup();
}

void UInflightGraphNodeBase::SetupLive(UInflightGraph* LiveGraph)
{
	Graph = LiveGraph;
}

void UInflightGraphNodeBase::Activate()
{
	if (!IsValid(GetGraph()))
	{
		UE_LOG(LogInflightGraph, Error, TEXT("<UInflightGraphNodeBase::Activate> Graph pointer is invalid!"))
		return;
	}

	OnActivated();
}

void UInflightGraphNodeBase::Deactivate()
{
	if (!IsValid(GetGraph()))
	{
		UE_LOG(LogInflightGraph, Error, TEXT("<UInflightGraphNodeBase::Activate> Graph pointer is invalid!"))
		return;
	}

	OnDeactivated();
}

void UInflightGraphNodeBase::OnSetup_Implementation()
{
	// This should always be overriden by first level children.
	check(0);
}

void UInflightGraphNodeBase::OnDeactivated_Implementation()
{
	// This should always be overriden by first level children.
	check(0);
}

void UInflightGraphNodeBase::OnActivated_Implementation()
{
	// This should always be overriden by first level children.
	check(0);
}

#undef LOCTEXT_NAMESPACE