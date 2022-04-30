// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightGraphNode.h"
#include "InflightGraph.generated.h"

UCLASS(Blueprintable)
class INFLIGHTGRAPH_API UInflightGraph : public UObject
{
	GENERATED_BODY()

public:
	UInflightGraph();

	UFUNCTION(BlueprintCallable, Category = "InflightGraph")
	int32 GetLevelNum() const;

	UFUNCTION(BlueprintCallable, Category = "InflightGraph")
	void GetNodesByLevel(int32 Level, TArray<UInflightGraphNode*>& Nodes);

	void ClearGraph();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "InflightGraph")
	TArray<TObjectPtr<UInflightGraphNode>> RootNodes;

	UPROPERTY(BlueprintReadOnly, Category = "InflightGraph")
	TArray<TObjectPtr<UInflightGraphNode>> AllNodes;
};