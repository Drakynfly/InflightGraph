// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraphNode_Action.h"
#include "InflightActionBase.h"

#define LOCTEXT_NAMESPACE "InflightGraphNode_Action"

FText UInflightGraphNode_Action::GetNodeCategory_Implementation(const UObject* Node) const
{
	return LOCTEXT("ActionCategory", "Actions");
}

FLinearColor UInflightGraphNode_Action::GetNodeTitleColor_Implementation(const UObject* Node)
{
	return FLinearColor::Red;
}

UInflightActionBase* UInflightGraphNode_Action::GetActionNode() const
{
	return GetNodeObject<UInflightActionBase>();
}

#undef LOCTEXT_NAMESPACE