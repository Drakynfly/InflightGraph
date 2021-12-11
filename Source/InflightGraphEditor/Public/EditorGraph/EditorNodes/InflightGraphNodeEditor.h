// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "Nodes/InflightGraphNode.h"
#include "InflightGraphNodeEditor.generated.h"

/**
 *
 */
UCLASS()
class UInflightGraphNodeEditor : public UEdGraphNode
{
	GENERATED_BODY()

public:
	UInflightGraphNodeEditor(const FObjectInitializer& ObjectInitializer);

	// Inherited via EdGraphNode.h
	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override; 	/** Create a visual widget to represent this node in a graph editor or graph panel.  If not implemented, the default node factory will be used. */
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PrepareForCopying() override;
	virtual void DestroyNode() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

public:
	virtual void SetAssetNode(UInflightGraphNode* InNode);
	virtual UInflightGraphNode* GetAssetNode();

	virtual void PostCopyNode();

	virtual bool RenameUniqueNode(const FText& NewName);

	virtual FText GetEdNodeName() const;
	virtual void SetEdNodeName(const FText& Name);
	virtual void SetEdNodeName(const FName& Name);

	virtual TSharedPtr<SWidget> GetContentWidget();

	virtual void UpdateVisualNode();

    virtual void SaveNodesAsChildren(TArray<UEdGraphNode*>& Children);
protected:
	virtual bool HasOutputPins();
	virtual bool HasInputPins();
	TSharedPtr<SGraphNode>SlateNode;
public:
	UPROPERTY(Instanced)
	UInflightGraphNode* AssetNode = nullptr;

protected:
	UPROPERTY()
	FText EdNodeName;

};