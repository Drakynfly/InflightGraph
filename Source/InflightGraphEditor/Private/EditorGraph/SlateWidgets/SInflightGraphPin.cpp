// Fill out your copyright notice in the Description page of Project Settings.
#include "EditorGraph/SlateWidgets/SInflightGraphPin.h"

#include "Utility/InflightGraphStyle.h"


void SInflightGraphPin::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	this->SetCursor(EMouseCursor::Default);

	bShowLabel = true;

	GraphPinObj = InPin;
	check(GraphPinObj != nullptr);

	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	check(Schema);

	SBorder::Construct(SBorder::FArguments()
		.BorderImage(this, &SInflightGraphPin::GetPinBorder)
		.BorderBackgroundColor(this, &SInflightGraphPin::GetPinColor)
		.OnMouseButtonDown(this, &SInflightGraphPin::OnPinMouseDown)
		.Cursor(this, &SInflightGraphPin::GetPinCursor)
		.Padding(FMargin(10.0f))
	);
}

FSlateColor SInflightGraphPin::GetPinColor() const
{
	return FInflightGraphStyle::FPin::Default;
}

TSharedRef<SWidget> SInflightGraphPin::GetDefaultValueWidget()
{
	return SNew(STextBlock);
}

const FSlateBrush* SInflightGraphPin::GetPinBorder() const
{
	return FEditorStyle::GetBrush(TEXT("Graph.StateNode.Body"));
}