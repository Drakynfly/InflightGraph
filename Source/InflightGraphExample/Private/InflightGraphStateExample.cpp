// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraphStateExample.h"
#include "InflightGraph.h"
#include "InflightGraphExampleModule.h"
#include "InflightGraphModule.h"

void UInflightGraphStateExample::OnSetup_Implementation()
{
#if WITH_EDITOR

	Graph->RegisterInputBinding("Movement");

#endif
}

void UInflightGraphStateExample::OnActivated_Implementation()
{
	UE_LOG(LogInflightGraphExample, Log, TEXT("Example Node going to bind input"));

	const UInputAction* MovementAction = Graph->GetRegisteredAction("Movement");

	if (!IsValid(MovementAction))
	{
		UE_LOG(LogInflightGraphExample, Warning, TEXT("<UInflightGraphStateExample::OnActivated_Implementation> MovementAction is invalid"))
		return;
	}

	if (const auto InputComp = Graph->GetInputComponent())
	{
		InputComp->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ThisClass::TextEvent);
	}
}

void UInflightGraphStateExample::TextEvent(const FInputActionValue& ActionValue)
{
	UE_LOG(LogInflightGraphExample, Log, TEXT("TEXT EVENT FIRED"));
}