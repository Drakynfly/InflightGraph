// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightLink_InputAction.h"

#include "InflightGraphModule.h"

#include "EnhancedInputComponent.h"
#include "InflightGraph.h"

#define LOCTEXT_NAMESPACE "InflightLink_InputAction"

UInflightLink_InputAction::UInflightLink_InputAction()
{
	GetInflightNodeSparse()->NodeTitle = LOCTEXT("NodeTitle_InputAction", "Input Link");
}

void UInflightLink_InputAction::OnActivated_Implementation()
{
	Super::OnActivated_Implementation();

	if (!IsValid(ActionBinding.Input))
	{
		UE_LOG(LogInflightGraph, Warning, TEXT("'%s': ActionBinding.InputAction is invalid"), *GetName())
		return;
	}

	if (ActionBinding.Trigger == ETriggerEvent::None)
	{
		UE_LOG(LogInflightGraph, Warning, TEXT("'%s': ActionBinding.Trigger is 'None'"), *GetName())
		return;
	}

	const FString LinkName = ActionBinding.Input->GetName();

	UE_LOG(LogInflightGraph, Log, TEXT("InputAction binding input to '%s'"), *LinkName);

	if (UEnhancedInputComponent* InputComp = GetInflightGraph()->GetInputComponent<UEnhancedInputComponent>())
	{
		InputLinkPtr = &InputComp->BindAction(ActionBinding.Input, ActionBinding.Trigger, this, &ThisClass::Trigger);
	}
}

void UInflightLink_InputAction::OnDeactivated_Implementation()
{
	Super::OnDeactivated_Implementation();

	if (InputLinkPtr != nullptr)
	{
		if (UEnhancedInputComponent* InputComp = GetInflightGraph()->GetInputComponent<UEnhancedInputComponent>())
		{
			InputComp->RemoveBinding(*InputLinkPtr);
		}
	}
}

void UInflightLink_InputAction::OnTriggered_Implementation(const FInputActionValue& ActionValue)
{
	UE_LOG(LogInflightGraph, Log, TEXT("Link %s binding triggered!"), *ActionBinding.Input.GetName());

	Super::OnTriggered_Implementation(ActionValue);
}

#undef LOCTEXT_NAMESPACE