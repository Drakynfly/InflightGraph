// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "InflightEditorGraphSchema.generated.h"

/**
 *
 */
UCLASS()
class UInflightEditorGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

public:
	UInflightEditorGraphSchema(const FObjectInitializer& ObjectInitializer)
	  : Super(ObjectInitializer) {}

	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;

	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;

	virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;

	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
};