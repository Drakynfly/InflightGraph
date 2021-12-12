// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "EditorGraph/EditorNodes/InflightEditorGraphNode.h"
#include "InflightEditorStartNode.generated.h"

/**
 *
 */
UCLASS()
class INFLIGHTEDITOR_API UInflightEditorStartNode : public UInflightEditorGraphNode
{
	GENERATED_BODY()

	virtual FText GetTooltipText() const override;

	virtual bool CanDuplicateNode() const override { return false; }
	virtual bool CanUserDeleteNode() const override { return false; }

	virtual bool AllowConnection(UInflightEditorGraphNode* Other, EEdGraphPinDirection OthersDirection, FText& OutErrorReason) override;

	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;

	virtual FLinearColor GetNodeBodyTintColor() const override { return FInflightGraphStyle::FNode::Start; }
};