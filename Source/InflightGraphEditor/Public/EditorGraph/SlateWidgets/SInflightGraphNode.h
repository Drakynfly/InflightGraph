﻿// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "SGraphNode.h"

/**
 *
 */
class SInflightGraphNode : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SInflightGraphNode) {}
	SLATE_END_ARGS()

	// Inherited via SGraphNode
	virtual void UpdateGraphNode() override;
	virtual void CreatePinWidgets() override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;

	void Construct(const FArguments& InArgs, UEdGraphNode* InNode);

protected:

	TSharedPtr<SBox> ContentWidget;
    TSharedPtr<STextBlock> NodeHeader;

	virtual void CreateContent();
    virtual void CreateHeader();
};