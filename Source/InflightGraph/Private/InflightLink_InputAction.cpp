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
		UE_LOG(LogInflightGraph, Warning, TEXT("InputAction %s InputAction is invalid"), *GetName())
		return;
	}

	const FString LinkName = ActionBinding.Input->GetName();

	UE_LOG(LogInflightGraph, Log, TEXT("InputAction binding input to '%s'"), *LinkName);

	if (UEnhancedInputComponent* InputComp = GetOuterUInflightGraph()->GetInputComponent<UEnhancedInputComponent>())
	{
		InputLinkPtr = &InputComp->BindAction(ActionBinding.Input, ActionBinding.Trigger, this, &ThisClass::ActionTrigger);
	}
}

void UInflightLink_InputAction::OnDeactivated_Implementation()
{
	Super::OnDeactivated_Implementation();

	if (InputLinkPtr != nullptr)
	{
		if (UEnhancedInputComponent* InputComp = GetOuterUInflightGraph()->GetInputComponent<UEnhancedInputComponent>())
		{
			InputComp->RemoveBinding(*InputLinkPtr);
		}
	}
}

void UInflightLink_InputAction::OnTriggered_Implementation()
{
	Super::OnTriggered_Implementation();

	UE_LOG(LogInflightGraph, Log, TEXT("Link %s binding triggered!"), *ActionBinding.Input.GetName());
}

void UInflightLink_InputAction::ActionTrigger(const FInputActionValue& ActionValue)
{
	Trigger();
}

#undef LOCTEXT_NAMESPACE