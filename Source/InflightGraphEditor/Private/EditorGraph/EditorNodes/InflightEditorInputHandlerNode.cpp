// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.


#include "EditorGraph/EditorNodes/InflightEditorInputHandlerNode.h"

bool UInflightEditorInputHandlerNode::AllowConnection(UInflightEditorGraphNode* Other,
                                                      const EEdGraphPinDirection OthersDirection, FText& OutErrorReason)
{
	return Super::AllowConnection(Other, OthersDirection, OutErrorReason);
}