// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightGraphNode.generated.h"

class UInflightGraph;
class UInflightGraphEdge;

UCLASS(Blueprintable)
class INFLIGHTGRAPH_API UInflightGraphNode : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "InflightGraphNode")
	virtual UInflightGraphEdge* GetEdge(UInflightGraphNode* ChildNode);

	// Does this node have any children
	UFUNCTION(BlueprintCallable, Category = "InflightGraphNode")
	bool IsLeafNode() const;

	UFUNCTION(BlueprintCallable, Category = "InflightGraphNode")
	UInflightGraph* GetGraph() const { return Graph; }

	UFUNCTION(BlueprintCallable, Category = "InflightGraphNode")
	TArray<UInflightGraphNode*> GetChildrenNodes() const { return ChildrenNodes; }

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "InflightGraphNode")
	TObjectPtr<UInflightGraph> Graph;

	UPROPERTY(BlueprintReadOnly, Category = "InflightGraphNode")
	TArray<TObjectPtr<UInflightGraphNode>> ParentNodes;

	UPROPERTY(BlueprintReadOnly, Category = "InflightGraphNode")
	TArray<TObjectPtr<UInflightGraphNode>> ChildrenNodes;

	UPROPERTY(BlueprintReadOnly, Category = "InflightGraphNode")
	TMap<TObjectPtr<UInflightGraphNode>, TObjectPtr<UInflightGraphEdge>> Edges;
};