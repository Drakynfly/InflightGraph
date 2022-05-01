// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightGraphNodeBase.h"
#include "InflightGraphLink.generated.h"

class UInflightGraph;

/**
 * A link between Action and State nodes inside an Inflight Graph
 */
UCLASS(Blueprintable)
class INFLIGHTGRAPH_API UInflightGraphLink : public UObject
{
	GENERATED_BODY()

public:
	UInflightGraph* GetGraph() const { return Graph; }
	UInflightGraphNodeBase* GetStartNode() const { return StartNode; }
	UInflightGraphNodeBase* GetEndNode() const { return EndNode; }

private:
	// The graph we are inside.
	UPROPERTY(BlueprintReadOnly, Category = "InflightGraphNode", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInflightGraph> Graph;

	// The node that can invoke us.
	UPROPERTY(BlueprintReadOnly, Category = "InflightGraphEdge", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInflightGraphNodeBase> StartNode;

	// The node that we invoke.
	UPROPERTY(BlueprintReadOnly, Category = "InflightGraphEdge", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInflightGraphNodeBase> EndNode;
};