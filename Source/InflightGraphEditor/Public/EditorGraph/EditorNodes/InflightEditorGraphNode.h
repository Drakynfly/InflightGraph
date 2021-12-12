// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "EdGraph/EdGraphNode.h"
#include "Nodes/InflightGraphNode.h"

// ReSharper disable once CppUnusedIncludeDirective
// Used by most children, so included here for sanity
#include "Utility/InflightGraphStyle.h"

#include "InflightEditorGraphNode.generated.h"

/**
 *
 */
UCLASS()
class INFLIGHTEDITOR_API UInflightEditorGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UInflightEditorGraphNode(const FObjectInitializer& ObjectInitializer);

	// Inherited via EdGraphNode.h
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override; 	/** Create a visual widget to represent this node in a graph editor or graph panel.  If not implemented, the default node factory will be used. */
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PrepareForCopying() override;
	virtual void DestroyNode() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
	virtual bool GetCanRenameNode() const override { return false; }

public:
	virtual bool AllowConnection(UInflightEditorGraphNode* Other, EEdGraphPinDirection OthersDirection, FText& OutErrorReason) { return true; }

	virtual void SetAssetNode(UInflightGraphNode* InNode);
	virtual UInflightGraphNode* GetAssetNode();

	virtual void PostCopyNode();

	virtual TSharedPtr<SWidget> GetContentWidget();

	virtual void UpdateVisualNode();

    virtual void SaveNodesAsChildren(TArray<UEdGraphNode*>& Children);

	bool BlueprintNode = false;

protected:
	virtual bool HasOutputPins();
	virtual bool HasInputPins();

	TSharedPtr<SGraphNode> SlateNode;

public:
	UPROPERTY(Instanced)
	UInflightGraphNode* AssetNode = nullptr;

protected:
	UPROPERTY()
	FText EdNodeName;
};