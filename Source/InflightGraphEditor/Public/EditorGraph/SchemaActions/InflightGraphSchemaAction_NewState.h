// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "EditorGraph/EditorNodes/InflightEditorStateNode.h"
#include "Templates/SubclassOf.h"
#include "Nodes/InflightGraphNode.h"
#include "InflightGraphSchemaAction_NewState.generated.h"

USTRUCT()
struct FInflightGraphSchemaAction : public FEdGraphSchemaAction
{
	GENERATED_BODY()

	FInflightGraphSchemaAction()
	  : FEdGraphSchemaAction()
	{}

	FInflightGraphSchemaAction(const FText InNodeCategory, const FText InMenuDesc, const FText InToolTip,
		const int32 InGrouping, const TSubclassOf<UInflightGraphNode> InNodeClass)
	  :	FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping),
		NewNodeClass(InNodeClass) {}

	virtual const FSlateBrush* GetIconBrush() const
	{
		return FEditorStyle::GetBrush("NoBrush");
	}

	virtual const FLinearColor& GetIconColor() const
	{
		static const FLinearColor DefaultColor;
		return DefaultColor;
	}

	/** Execute this action, given the graph and schema, and possibly a pin that we were dragged from. Returns a node that was created by this action (if any). */
	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;

	virtual UInflightEditorGraphNode* CreateEditorNode(UEdGraph* ParentGraph, bool bSelectNewNode, UInflightGraphNode* AssetNode) { return nullptr; }

	TSubclassOf<UInflightGraphNode> NewNodeClass = nullptr;
	bool IsForBlueprintClass = false;
};

/**
 *
 */
USTRUCT()
struct FInflightGraphSchemaAction_NewState : public FInflightGraphSchemaAction
{
public:
	GENERATED_BODY()

	FInflightGraphSchemaAction_NewState()
		: FInflightGraphSchemaAction()
	{}

	FInflightGraphSchemaAction_NewState(const FText InNodeCategory, const FText InMenuDesc, const FText InToolTip,
		const int32 InGrouping, const TSubclassOf<UInflightGraphNode> InNodeClass)
  :	FInflightGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping, InNodeClass) {}

    virtual UInflightEditorGraphNode* CreateEditorNode(UEdGraph* ParentGraph, bool bSelectNewNode, UInflightGraphNode* AssetNode) override;
};

/**
 *
 */
USTRUCT()
struct FInflightGraphSchemaAction_NewInputHandler : public FInflightGraphSchemaAction
{
public:
	GENERATED_BODY()

	FInflightGraphSchemaAction_NewInputHandler()
	  : FInflightGraphSchemaAction()
	{}

	FInflightGraphSchemaAction_NewInputHandler(const FText InNodeCategory, const FText InMenuDesc, const FText InToolTip,
		const int32 InGrouping, const TSubclassOf<UInflightGraphNode> InNodeClass)
	  :	FInflightGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping, InNodeClass) {}

	virtual UInflightEditorGraphNode* CreateEditorNode(UEdGraph* ParentGraph, bool bSelectNewNode, UInflightGraphNode* AssetNode) override;
};