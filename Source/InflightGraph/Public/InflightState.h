// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightNodeBase.h"
#include "InflightState.generated.h"

class UInputMappingContext;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInflightStateTrigger);

/**
 *
 */
UCLASS(Blueprintable)
class INFLIGHTGRAPH_API UInflightState : public UInflightNodeBase
{
	GENERATED_BODY()

	friend class UInflightLinkBase;

public:
	UInflightState();

protected:
	virtual void OnActivated_Implementation() override;
	virtual void OnDeactivated_Implementation() override;
	virtual void OnTriggered_Implementation(const FInputActionValue& ActionValue) override;

public:
	FString GetStateName() const;
	FText GetStateTitle() const;

	UPROPERTY(BlueprintAssignable, Category = "Inflight State")
	FInflightStateTrigger EventOnActivated;

	UPROPERTY(BlueprintAssignable, Category = "Inflight State")
	FInflightStateTrigger EventOnDeactivated;

	UPROPERTY(BlueprintAssignable, Category = "Inflight State")
	FInflightStateTrigger EventOnTriggered;

protected:
	// Input mapping contexts to make active while this state is activated.
	UPROPERTY(EditAnywhere, Category = "State")
	TSet<TObjectPtr<UInputMappingContext>> Mappings;

	// Internal name to identify this state in the graph.
	UPROPERTY(EditAnywhere, Category = "State")
	FString StateName;

	// Displayable title for showing this state to the player.
	UPROPERTY(EditAnywhere, Category = "State")
	FText StateTitle;
};