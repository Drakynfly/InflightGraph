﻿// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "UObject/Object.h"
#include "InflightNodeBase.generated.h"

struct FInputActionValue;
class UInflightGraph;
class UInflightLinkBase;

USTRUCT()
struct FInflightNodeSparse
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Inflight Node Class")
	FText NodeTitle;
};

/**
 *
 */
UCLASS(Abstract, SparseClassDataTypes = "InflightNodeSparse")
class INFLIGHTGRAPH_API UInflightNodeBase : public UObject
{
	GENERATED_BODY()

public:
	UInflightGraph* GetInflightGraph() const;

#if WITH_EDITOR
	void SetLinkedNodes(const TSet<TObjectPtr<UInflightNodeBase>>& Nodes);
#endif

	// Is this node listening for Triggers
	UFUNCTION(BlueprintCallable, Category = "Inflight|Node")
	bool IsActive() const;

	UFUNCTION(BlueprintCallable, Category = "Inflight|Node")
	TArray<UInflightNodeBase*> GetLinkedNodes() const;

	void AddActivationTrigger(UObject* Trigger);
	void RemoveActivationTrigger(UObject* Trigger);
	void Trigger(const FInputActionValue& ActionValue);

private:
	void Activate();
	void Deactivate();

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Inflight|Node")
	void OnActivated();

	UFUNCTION(BlueprintNativeEvent, Category = "Inflight|Node")
	void OnDeactivated();

	UFUNCTION(BlueprintNativeEvent, Category = "Inflight|Node")
	void OnTriggered(const FInputActionValue& ActionValue);

private:
	UPROPERTY()
	bool Activated = false;

	// Objects keeping us active
	UPROPERTY()
	TArray<TWeakObjectPtr<UObject>> ActivationTriggers;

	UPROPERTY(VisibleAnywhere)
	TSet<TObjectPtr<UInflightNodeBase>> LinkedNodes;
};
