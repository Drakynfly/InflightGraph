// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InflightGraphNode.h"
#include "InflightGraphEdge.generated.h"

class UInflightGraph;

UCLASS(Blueprintable)
class INFLIGHTGRAPH_API UInflightGraphEdge : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "InflightGraphNode")
	UInflightGraph* Graph;

	UPROPERTY(BlueprintReadOnly, Category = "InflightGraphEdge")
	UInflightGraphNode* StartNode;

	UPROPERTY(BlueprintReadOnly, Category = "InflightGraphEdge")
	UInflightGraphNode* EndNode;

	UFUNCTION(BlueprintPure, Category = "InflightGraphEdge")
	UInflightGraph* GetGraph() const;
};