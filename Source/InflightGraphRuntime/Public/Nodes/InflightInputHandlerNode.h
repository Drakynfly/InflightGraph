// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/InflightGraphNode.h"
#include "InflightInputHandlerNode.generated.h"

enum class ETriggerEvent : uint8;
class UInputAction;

/**
 *
 */
UCLASS()
class INFLIGHTGRAPHRUNTIME_API UInflightInputHandlerNode : public UInflightGraphNode
{
	GENERATED_BODY()

	friend class UInflightStateNode;

	UInflightInputHandlerNode();

protected:

	void OnParentActivate(UInflightStateNode* Parent);

	void OnParentDeactivate();

	UFUNCTION()
	void OnInputTriggered();

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input Handler")
	TObjectPtr<UInputAction> Action;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input Handler")
	ETriggerEvent Trigger;

private:
	/** The parent node currently active on the Inflight Graph */
	UPROPERTY()
	TObjectPtr<UInflightStateNode> ActiveParent;

	struct FEnhancedInputActionEventBinding* BindingHandle = nullptr;
};