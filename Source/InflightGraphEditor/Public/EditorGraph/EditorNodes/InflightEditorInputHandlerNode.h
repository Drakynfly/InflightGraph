// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorGraph/EditorNodes/InflightEditorGraphNode.h"
#include "InflightEditorInputHandlerNode.generated.h"

/**
 *
 */
UCLASS()
class INFLIGHTEDITOR_API UInflightEditorInputHandlerNode : public UInflightEditorGraphNode
{
	GENERATED_BODY()

	virtual bool AllowConnection(UInflightEditorGraphNode* Other, EEdGraphPinDirection OthersDirection, FText& OutErrorReason) override;

	virtual FLinearColor GetNodeBodyTintColor() const override { return FInflightGraphStyle::FNode::Input; }
};