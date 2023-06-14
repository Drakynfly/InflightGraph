// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraphNode_State.h"

#include "InflightGraph.h"
#include "InflightState.h"

#define LOCTEXT_NAMESPACE "InflightGraphNode_Action"

FText UInflightGraphNode_State::GetNodeTitle_Implementation(const UObject* Node, const EHeartNodeNameContext Context) const
{
	switch (Context)
	{
	case EHeartNodeNameContext::NodeInstance:
		if (auto&& StateNode = Cast<UInflightState>(Node))
		{
			const FText NodeTitle = StateNode->GetStateTitle();
			return FText::Format(LOCTEXT("NodeTitle_InstanceFormat", "{0}\nState"), NodeTitle);
		}
		break;
	case EHeartNodeNameContext::Default:
	case EHeartNodeNameContext::Palette:
		return LOCTEXT("NodeTitle_PaletteTitle", "New State...");
	default: ;
	}

	return Super::GetNodeTitle_Implementation(Node, Context);
}

FText UInflightGraphNode_State::GetNodeCategory_Implementation(const UObject* Node) const
{
	return LOCTEXT("StateCategory", "State");
}

FLinearColor UInflightGraphNode_State::GetNodeTitleColor_Implementation(const UObject* Node)
{
	return FLinearColor(FColor::Cyan);
}

UInflightState* UInflightGraphNode_State::GetStateNode() const
{
	return GetNodeObject<UInflightState>();
}

#undef LOCTEXT_NAMESPACE