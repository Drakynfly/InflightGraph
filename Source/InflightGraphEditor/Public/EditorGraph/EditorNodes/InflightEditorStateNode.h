// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EditorGraph/EditorNodes/InflightEditorGraphNode.h"
#include "InflightEditorStateNode.generated.h"

/**
 *
 */
UCLASS()
class INFLIGHTEDITOR_API UInflightEditorStateNode : public UInflightEditorGraphNode
{
	GENERATED_BODY()

	virtual bool AllowConnection(UInflightEditorGraphNode* Other, EEdGraphPinDirection OthersDirection, FText& OutErrorReason) override;

	virtual FLinearColor GetNodeBodyTintColor() const override { return FInflightGraphStyle::FNode::State; }
};