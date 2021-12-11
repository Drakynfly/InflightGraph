// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "SGraphPin.h"

/**
 *
 */
class SInflightGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SInflightGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);

protected:
	virtual FSlateColor GetPinColor() const override;

	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;

	virtual const FSlateBrush* GetPinBorder() const;
};