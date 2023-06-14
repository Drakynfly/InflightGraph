// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightLinkBase.h"
#include "InputTriggers.h"
#include "InflightLink_InputAction.generated.h"

USTRUCT()
struct FLinkActionBinding
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "LinkActionBinding")
	TObjectPtr<UInputAction> Input;

	UPROPERTY(EditAnywhere, Category = "LinkActionBinding")
	ETriggerEvent Trigger = ETriggerEvent::None;
};

/**
 *
 */
UCLASS()
class INFLIGHTGRAPH_API UInflightLink_InputAction : public UInflightLinkBase
{
	GENERATED_BODY()

public:
	UInflightLink_InputAction();

protected:
	virtual void OnActivated_Implementation() override;
	virtual void OnDeactivated_Implementation() override;
	virtual void OnTriggered_Implementation(const FInputActionValue& ActionValue) override;

	UPROPERTY(EditAnywhere)
	FLinkActionBinding ActionBinding;

private:
	struct FEnhancedInputActionEventBinding* InputLinkPtr = nullptr;
};