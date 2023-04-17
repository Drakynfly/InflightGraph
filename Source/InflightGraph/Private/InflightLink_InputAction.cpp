// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightLink_InputAction.h"

#include "InflightGraph.h"
#include "InflightGraphModule.h"

#include "EnhancedInputComponent.h"

void UInflightLink_InputAction::OnSetup()
{
	Super::OnSetup();

#if WITH_EDITOR
	Graph->RegisterInputBinding(ActionBinding.LinkName);
#endif
}

void UInflightLink_InputAction::OnActivated()
{
	Super::OnActivated();

	UE_LOG(LogInflightGraph, Log, TEXT("GraphLink %s binding input"), *ActionBinding.LinkName.ToString());

	const UInputAction* MovementAction = Graph->GetRegisteredAction(ActionBinding.LinkName);

	if (!IsValid(MovementAction))
	{
		UE_LOG(LogInflightGraph, Warning, TEXT("GraphLink %s MovementAction is invalid"), *ActionBinding.LinkName.ToString())
		return;
	}

	if (UEnhancedInputComponent* InputComp = Graph->GetInputComponent<UEnhancedInputComponent>())
	{
		InputLinkPtr = &InputComp->BindAction(MovementAction, ActionBinding.Trigger, this, &ThisClass::ActionTrigger);
	}
}

void UInflightLink_InputAction::OnDeactivated()
{
	Super::OnDeactivated();

	if (InputLinkPtr != nullptr)
	{
		if (UEnhancedInputComponent* InputComp = Graph->GetInputComponent<UEnhancedInputComponent>())
		{
			InputComp->RemoveBinding(*InputLinkPtr);
		}
	}
}

void UInflightLink_InputAction::OnTriggered()
{
	UE_LOG(LogInflightGraph, Log, TEXT("Link %s binding triggered!"), *ActionBinding.LinkName.ToString());

	Super::OnTriggered();
}

void UInflightLink_InputAction::ActionTrigger(const FInputActionValue& ActionValue)
{
	Trigger();
}