// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightGraphNodeBase.h"
#include "InflightLinkBase.generated.h"

class UInflightGraph;

/**
 * Base class for links between Action and State nodes inside an Inflight Graph
 */
UCLASS(Abstract, Blueprintable)
class INFLIGHTGRAPH_API UInflightLinkBase : public UObject
{
	GENERATED_BODY()

public:
	FString GetLinkName() const { return Name; }
	UInflightGraph* GetGraph() const { return Graph; }
	TArray<UInflightGraphNodeBase*> GetStartNodes() const { return StartNodes; }
	TArray<UInflightGraphNodeBase*> GetEndNodes() const { return EndNodes; }

	void SetName(const FString& InName);

	void Setup(UInflightGraph* InflightGraph, UInflightGraphNodeBase* NodeA, UInflightGraphNodeBase* NodeB);

	void Activate();

	void Deactivate();

	UFUNCTION(BlueprintCallable, Category = "Inflight Link")
	void Trigger();

	// Triggered when our start node becomes active.
	virtual void OnSetup();

	// Triggered when our start node becomes active.
	virtual void OnActivated();

	virtual void OnDeactivated();

	virtual void OnTriggered();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Inflight Link")
	FString Name;

	// The graph we are inside.
	UPROPERTY(BlueprintReadOnly, Category = "Inflight Link")
	TObjectPtr<UInflightGraph> Graph;

	// The nodes that can invoke us.
	UPROPERTY(BlueprintReadOnly, Category = "Inflight Link")
	TArray<TObjectPtr<UInflightGraphNodeBase>> StartNodes;

	// The nodes that we invoke.
	UPROPERTY(BlueprintReadOnly, Category = "Inflight Link")
	TArray<TObjectPtr<UInflightGraphNodeBase>> EndNodes;
};