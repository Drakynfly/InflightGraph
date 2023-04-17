// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightGraphNodeBase.h"
#include "InflightState.generated.h"

class UInputMappingContext;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInflightStateTrigger);

/**
 *
 */
UCLASS(Blueprintable)
class INFLIGHTGRAPH_API UInflightState : public UInflightGraphNodeBase
{
	GENERATED_BODY()

	friend class UInflightLinkBase;

protected:
	virtual void OnSetup_Implementation() override;
	virtual void OnTriggered_Implementation() override;
	virtual void OnActivated_Implementation() override;
	virtual void OnDeactivated_Implementation() override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Inflight State")
	FInflightStateTrigger EventOnTriggered;

	UPROPERTY(BlueprintAssignable, Category = "Inflight State")
	FInflightStateTrigger EventOnActivated;

	UPROPERTY(BlueprintAssignable, Category = "Inflight State")
	FInflightStateTrigger EventOnDeactivated;

//protected:
	// Input mapping contexts to make active while this state is activated.
	UPROPERTY()
	TArray<TObjectPtr<UInputMappingContext>> Contexts;
};