// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraphNode_Link.h"

#include "InflightLinkBase.h"

#define LOCTEXT_NAMESPACE "InflightGraphNode_Action"

FText UInflightGraphNode_Link::GetNodeCategory_Implementation(const UObject* Node) const
{
	return LOCTEXT("ActionCategory", "Link");
}

FLinearColor UInflightGraphNode_Link::GetNodeTitleColor_Implementation(const UObject* Node)
{
	return FMath::Lerp<FLinearColor>(FColor::Green, FColor::Yellow, 0.5);
}

UInflightLinkBase* UInflightGraphNode_Link::GetLinkNode() const
{
	return GetNodeObject<UInflightLinkBase>();
}

#undef LOCTEXT_NAMESPACE