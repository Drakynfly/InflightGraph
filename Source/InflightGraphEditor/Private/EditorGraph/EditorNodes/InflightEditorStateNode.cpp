// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "EditorGraph/EditorNodes/InflightEditorStateNode.h"
#include "EditorGraph/EditorNodes/InflightEditorInputHandlerNode.h"

#define LOCTEXT_NAMESPACE "InflightEditorStateNode"

bool UInflightEditorStateNode::AllowConnection(UInflightEditorGraphNode* Other, const EEdGraphPinDirection OthersDirection, FText& OutErrorReason)
{
	// When connecting ourselves to another nodes input, ensure that node is a InputHandlerNode
	if (OthersDirection == EGPD_Input)
	{
		if (!Other->IsA<UInflightEditorInputHandlerNode>())
		{
			OutErrorReason = LOCTEXT("ConnectionError", "State Nodes can only connect output to Input Handlers");
			return false;
		}
	}

	return true;
}

#undef LOCTEXT_NAMESPACE