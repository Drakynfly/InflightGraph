// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "UObject/NoExportTypes.h"
#include "InflightGraphNode.generated.h"

class UInflightGraph;

/**
 * Base abstract class for every node of the graph.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class INFLIGHTGRAPHRUNTIME_API UInflightGraphNode : public UObject
{
	GENERATED_BODY()

public:
	UInflightGraphNode();

	virtual void SetGraph(UInflightGraph* InGraph);
	virtual UInflightGraph* GetGraph();
	virtual bool HasParentNodes();
	virtual void LinkArgumentNodeAsChild(UInflightGraphNode* Child);
	virtual void ClearLinks();
	virtual bool RemoveLinkedNode(UInflightGraphNode* NodeToRemove);
	virtual bool RemoveNodeFromParents(UInflightGraphNode* NodeToRemove);
	virtual bool RemoveNodeFromChildren(UInflightGraphNode* NodeToRemove);

	// @todo these should not be in runtime. these should be in editor.
	virtual bool HasInputPins() const { return true; }
	virtual bool HasOutputPins() const { return true; }

	UFUNCTION(BlueprintPure, Category = "Node Data")
	TArray<UInflightGraphNode*> GetParents();

	// @todo this should not be in runtime. this should be in editor.
    UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "Node Data")
	FText GetNodeTitle();
    virtual FText GetNodeTitle_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Node Data")
	UInflightGraphNode* GetNodePointer();
    virtual UInflightGraphNode* GetNodePointer_Implementation();

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UInflightGraph> Graph = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<UInflightGraphNode>> ParentNodes;

    UPROPERTY()
	FText DefaultNodeTitle = FText();
};