// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "EnhancedInputComponent.h"
#include "InflightLinkBase.h"
#include "InflightLink_InputAction.generated.h"

USTRUCT()
struct FLinkActionBinding
{
	GENERATED_BODY()

	UPROPERTY()
	FName LinkName;

	UPROPERTY()
	ETriggerEvent Trigger = ETriggerEvent::None;
};

/**
 *
 */
UCLASS()
class INFLIGHTGRAPH_API UInflightLink_InputAction : public UInflightLinkBase
{
	GENERATED_BODY()

	virtual void OnSetup() override;
	virtual void OnActivated() override;
	virtual void OnDeactivated() override;
	virtual void OnTriggered() override;

	void ActionTrigger(const FInputActionValue& ActionValue);

public:
	UPROPERTY()
	FLinkActionBinding ActionBinding;

private:
	struct FEnhancedInputActionEventBinding* InputLinkPtr = nullptr;
};