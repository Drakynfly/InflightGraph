// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraphNodeBase.h"

#include "InflightNodeBase.h"

FText UInflightGraphNodeBase::GetNodeTitle_Implementation(const UObject* Node, EHeartNodeNameContext Context) const
{
	if (const UInflightNodeBase* InflightNode = Cast<UInflightNodeBase>(Node))
	{
		FText NodeTitle = InflightNode->GetInflightNodeSparse()->NodeTitle;
		if (!NodeTitle.IsEmpty())
		{
			return NodeTitle;
		}
	}
	return Super::GetNodeTitle_Implementation(Node, Context);
}

#if WITH_EDITOR
void UInflightGraphNodeBase::AddParentLink(UInflightLinkBase* Node, UInflightNodeBase* Link)
{
}

void UInflightGraphNodeBase::AddChildLink(UInflightLinkBase* Node, UInflightNodeBase* Link)
{
}
#endif
