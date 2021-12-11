// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "Templates/SubclassOf.h"
#include "Nodes/InflightGraphNode.h"
#include "InflightEditorGraph_NewNode_SchemaAction.generated.h"

/**
 *
 */
USTRUCT()
struct FInflightEditorGraph_NewNode_SchemaAction : public FEdGraphSchemaAction
{
public:
	GENERATED_BODY()

	FInflightEditorGraph_NewNode_SchemaAction()
		: FEdGraphSchemaAction(), NewNodeClass(nullptr)
	{}

	FInflightEditorGraph_NewNode_SchemaAction(const FText InNodeCategory, const FText InMenuDesc, const FText InToolTip,
		const int32 InGrouping, const TSubclassOf<UInflightGraphNode> InNodeClass)
  :	FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping), NewNodeClass(InNodeClass) {}

	/** Execute this action, given the graph and schema, and possibly a pin that we were dragged from. Returns a node that was created by this action (if any). */
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;

    virtual UEdGraphNode* CreateEditorNode(UEdGraph* ParentGraph, bool bSelectNewNode, UInflightGraphNode* AssetNode);

	TSubclassOf<UInflightGraphNode>NewNodeClass;
};