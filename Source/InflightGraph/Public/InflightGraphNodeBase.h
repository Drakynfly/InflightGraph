// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightGraphNodeBase.generated.h"

class UInflightGraph;
class UInflightLinkBase;

/**
 * Base class for logic nodes inside an inflight graph.
 */
UCLASS(Abstract)
class INFLIGHTGRAPH_API UInflightGraphNodeBase : public UObject
{
	GENERATED_BODY()

public:
	FString GetNodeName() { return Name; }

	UInflightGraph* GetGraph() const { return !Graph.IsNullNoResolve() ? Graph : nullptr; }

	void AddParentLink(UInflightGraphNodeBase* Node, UInflightLinkBase* Link);

	void AddChildLink(UInflightGraphNodeBase* Node, UInflightLinkBase* Link);

	UFUNCTION(BlueprintCallable, Category = "Inflight Graph Node")
	TArray<UInflightGraphNodeBase*> GetChildrenNodes() const { return ChildrenNodes; }

	// Find the Link Object for a child.
	UFUNCTION(BlueprintCallable, Category = "Inflight Graph Node")
	UInflightLinkBase* GetChildLink(UInflightGraphNodeBase* ChildNode) const;

	// Is this node listening for Triggers
	UFUNCTION(BlueprintCallable, Category = "Inflight Graph Node")
	bool IsActive() const;

	// Does this node have no parents
	UFUNCTION(BlueprintCallable, Category = "Inflight Graph Node")
	bool IsRootNode() const;

	// Does this node have no children
	UFUNCTION(BlueprintCallable, Category = "Inflight Graph Node")
	bool IsLeafNode() const;

	void Setup(UInflightGraph* InGraph, const FString& InName);

	void Trigger();

	void AddActivationTrigger(UObject* Trigger);

	void RemoveActivationTrigger(UObject* Trigger);

private:
	void Activate();

	void Deactivate();

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Inflight Graph Node")
	void OnSetup();

	UFUNCTION(BlueprintNativeEvent, Category = "Inflight Graph Node")
	void OnTriggered();

	UFUNCTION(BlueprintNativeEvent, Category = "Inflight Graph Node")
	void OnActivated();

	UFUNCTION(BlueprintNativeEvent, Category = "Inflight Graph Node")
	void OnDeactivated();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inflight Graph Node")
	FString Name;

	// Owning graph.
	UPROPERTY(BlueprintReadOnly, Category = "Inflight Graph Node")
	TObjectPtr<UInflightGraph> Graph = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Inflight Graph Node")
	TArray<TObjectPtr<UInflightGraphNodeBase>> ParentNodes;

	UPROPERTY(BlueprintReadOnly, Category = "Inflight Graph Node")
	TArray<TObjectPtr<UInflightGraphNodeBase>> ChildrenNodes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inflight Graph Node")
	TMap<TObjectPtr<UInflightLinkBase>, TObjectPtr<UInflightGraphNodeBase>> Links;

private:
	UPROPERTY()
	bool Activated = false;

	// Objects keeping us active
	UPROPERTY()
	TArray<TWeakObjectPtr<UObject>> ActivationTriggers;
};