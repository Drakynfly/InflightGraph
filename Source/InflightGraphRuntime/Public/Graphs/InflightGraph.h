// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "InflightGraph.generated.h"

class UInflightGraphNode;

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class INFLIGHTGRAPHRUNTIME_API UInflightGraph : public UObject
{
	GENERATED_BODY()

public:
	UInflightGraph();

	UFUNCTION(BlueprintCallable, Category = "Graph Data")
	void InitGraph(UObject* ParentObject);

#if WITH_EDITORONLY_DATA
	template <class T>
	T* SpawnNodeInsideGraph(const TSubclassOf<UInflightGraphNode> InNodeClass)
	{
		T* NewNode = NewObject<T>(this, InNodeClass, NAME_None, RF_Transactional);
		AddNode(NewNode);
		return NewNode;
	}

	virtual void AddNode(UInflightGraphNode* InNode);
	virtual void RemoveNode(UInflightGraphNode* NodeToRemove);
#endif

#if WITH_EDITORONLY_DATA
public:
	UPROPERTY()
	class UEdGraph* EdGraph;
#endif

	UPROPERTY(BlueprintReadOnly, Category = "Graph Data")
	TArray<UInflightGraphNode*>Nodes;

	UPROPERTY(BlueprintReadOnly, Category = "Graph Data")
	TMap<FString, UInflightGraphNode*>NamedNodes;

	UPROPERTY(BlueprintReadOnly, Category = "Graph Data")
	TMap<UInflightGraphNode*, FString>NodesNames;

	UPROPERTY(BlueprintReadWrite, Category = "Graph Data")
	UObject* Owner;
};