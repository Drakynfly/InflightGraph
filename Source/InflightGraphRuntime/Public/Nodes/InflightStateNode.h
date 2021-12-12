// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InflightInputHandlerNode.h"
#include "Nodes/InflightGraphNode.h"
#include "InflightStateNode.generated.h"

/**
 *
 */
UCLASS(Abstract)
class INFLIGHTGRAPHRUNTIME_API UInflightStateNode : public UInflightGraphNode, public FTickableGameObject
{
	GENERATED_BODY()

	friend class UInflightGraph;

public:
	// FTickableGameObject Implementation
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UInflightStateNode, STATGROUP_Tickables); }
	virtual bool IsTickable() const override { return Ticking; }
	virtual void Tick(float DeltaTime) override;
	// End FTickableGameObject Implementation

	virtual void LinkArgumentNodeAsChild(UInflightGraphNode* Child) override;
	virtual bool RemoveNodeFromChildren(UInflightGraphNode* NodeToRemove) override;
	virtual void ClearLinks() override;

private: // Called by UInflightGraph
	void SetActive();
	void SetInactive();

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Activation")
	void OnBecomeActive();

	UFUNCTION(BlueprintNativeEvent, Category = "Activation")
	void OnBecomeInactive();

public:
	UFUNCTION(BlueprintPure, Category =  "Activation")
	bool IsActive() const { return Active; }

protected:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Inflight State Node")
	bool NeedsToTick;

	UPROPERTY(BlueprintReadOnly, Category = "Inflight State Node")
	TArray<TObjectPtr<UInflightInputHandlerNode>> InputStack;
private:

	bool Active;

	bool Ticking;
};