// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InflightGraphNode.generated.h"

class UInflightGraph;

/**
 * Base abstract class for every node of the graph.
 */
UCLASS(Blueprintable, BlueprintType)
class INFLIGHTGRAPHRUNTIME_API UInflightGraphNode : public UObject
{
	GENERATED_BODY()

public:
	UInflightGraphNode();

	UFUNCTION(BlueprintPure, Category = "Node Data")
	TArray<UInflightGraphNode*> GetChildren();

	UFUNCTION(BlueprintPure, Category = "Node Data")
	TArray<UInflightGraphNode*> GetParents();

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "Node Data")
	FText GetNodeTitle();
    virtual FText GetNodeTitle_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "Node Data")
	bool HasInputPins();

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "Node Data")
	bool HasOutputPins();

	UFUNCTION(BlueprintNativeEvent, Category = "Node Data")
	UInflightGraphNode* GetNodePointer();
    virtual UInflightGraphNode* GetNodePointer_Implementation();

	virtual void SetGraph(UInflightGraph* InGraph);
	virtual UInflightGraph* GetGraph();
	virtual void AddToChildren(UInflightGraphNode* NewChildNode);
	virtual void AddToParent(UInflightGraphNode* NewParentNode);
	virtual bool HasParentNodes();
	virtual void LinkArgumentNodeAsChild(UInflightGraphNode* Child);
	virtual void ClearLinks();
	virtual bool RemoveLinkedNode(UInflightGraphNode* NodeToRemove);
	virtual bool RemoveNodeFromParents(UInflightGraphNode* NodeToRemove);
	virtual bool RemoveNodeFromChildren(UInflightGraphNode* NodeToRemove);

protected:
	UPROPERTY()
	TObjectPtr<UInflightGraph> Graph = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<UInflightGraphNode>> ParentNodes;

	UPROPERTY()
	TArray<TObjectPtr<UInflightGraphNode>> ChildNodes;

    UPROPERTY()
	bool bHasInputPins = true;

    UPROPERTY()
	bool bHasOutputPins = true;

    UPROPERTY()
	FText DefaultNodeTitle = FText();
};