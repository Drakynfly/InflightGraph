// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "EditorGraph/EditorNodes/InflightEditorStartNode.h"
#include "EditorGraph/EditorNodes/InflightEditorStateNode.h"
#include "Nodes/InflightStateNode.h"

#define LOCTEXT_NAMESPACE "InflightEditorStartNode"

FText UInflightEditorStartNode::GetTooltipText() const
{
	return Super::GetTooltipText();
}

bool UInflightEditorStartNode::AllowConnection(UInflightEditorGraphNode* Other, const EEdGraphPinDirection OthersDirection,
	FText& OutErrorReason)
{
	// Only allow connections to State Nodes.
	if (!Other->IsA(UInflightEditorStateNode::StaticClass()))
	{
		OutErrorReason = LOCTEXT("ConnectionError", "The Start Node can only connect to State Nodes");
		return false;
	}

	return true;
}

void UInflightEditorStartNode::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	// The user can do nothing to the Start Node.
}

#undef LOCTEXT_NAMESPACE