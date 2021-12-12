// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.


#include "Nodes/InflightInputHandlerNode.h"
#include "Graphs/InflightGraph.h"
#include "Nodes/InflightStateNode.h"

#include "EnhancedInputComponent.h"

#define LOCTEXT_NAMESPACE "InflightInputHandlerNode"

UInflightInputHandlerNode::UInflightInputHandlerNode()
{
	DefaultNodeTitle = LOCTEXT("NodeTitle", "Input Handler");
}

void UInflightInputHandlerNode::OnParentActivate(UInflightStateNode* Parent)
{
	ActiveParent = Parent;
	check(ActiveParent);

	APawn* Pawn = Parent->GetGraph()->GetAgent<APawn>();

	if (!Pawn)
	{
		return;
	}

	// @todo check this in compilation not runtime
	if (!Action)
	{
		UE_LOG(LogInflightGraph, Error, TEXT("Input Action is Invalid in UInflightInputHandlerNode"))
		return;
	}

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(Pawn->InputComponent))
	{
		BindingHandle = &Input->BindAction(Action, ETriggerEvent::Triggered, this, &ThisClass::OnInputTriggered);
	}
}

void UInflightInputHandlerNode::OnParentDeactivate()
{
	APawn* Pawn = ActiveParent->GetGraph()->GetAgent<APawn>();

	if (!Pawn)
	{
		return;
	}

	if (!BindingHandle)
	{
		return;
	}

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(Pawn->InputComponent))
	{
		Input->RemoveBinding(*BindingHandle);
	}
}

void UInflightInputHandlerNode::OnInputTriggered()
{
	UE_LOG(LogTemp, Warning, TEXT("Input From Handler Triggered"))
}

#undef LOCTEXT_NAMESPACE