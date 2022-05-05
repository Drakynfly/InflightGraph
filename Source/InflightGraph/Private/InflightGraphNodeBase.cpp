// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraphNodeBase.h"
#include "InflightGraph.h"
#include "InflightGraphModule.h"
#include "InflightLinkBase.h"

#define LOCTEXT_NAMESPACE "InflightGraphNode"

void UInflightGraphNodeBase::AddParentLink(UInflightGraphNodeBase* Node, UInflightLinkBase* Link)
{
	if (IsValid(Node) && IsValid(Link))
	{
		ParentNodes.Add(Node);
		Links.Add(Link, Node);
	}
}

void UInflightGraphNodeBase::AddChildLink(UInflightGraphNodeBase* Node, UInflightLinkBase* Link)
{
	if (IsValid(Node) && IsValid(Link))
	{
		ChildrenNodes.Add(Node);
		Links.Add(Link, Node);
	}
}

UInflightLinkBase* UInflightGraphNodeBase::GetChildLink(UInflightGraphNodeBase* ChildNode) const
{
	UE_LOG(LogInflightGraph, Log, TEXT("Looking for link to ChildNode: %s"), *ChildNode->Name);

	UInflightLinkBase* FoundLink = nullptr;

	// Filter links by those that have the ChildNode as an end node. This filters out looping links, where children and
	// parents both link to each other.
	TMap<TObjectPtr<UInflightLinkBase>, TObjectPtr<UInflightGraphNodeBase>> Filtered = Links.FilterByPredicate(
		[ChildNode, &FoundLink]	(const TTuple<TObjectPtr<UInflightLinkBase>, TObjectPtr<UInflightGraphNodeBase>>& Pair)
		{
			if (IsValid(Pair.Key))
			{
				if (Pair.Key->GetEndNode() == ChildNode)
				{
					FoundLink = Pair.Key;
				}
			}

			return false;
		});

	return FoundLink;
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

void UInflightGraphNodeBase::Trigger()
{
	OnTriggered();
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

void UInflightGraphNodeBase::OnTriggered_Implementation()
{
	// This should always be overriden by first level children.
	check(0);
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