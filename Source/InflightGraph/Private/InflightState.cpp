// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightState.h"

#include "EnhancedInputSubsystems.h"
#include "InflightGraph.h"
#include "InflightGraphModule.h"
#include "InflightLinkBase.h"

#define LOCTEXT_NAMESPACE "InflightState"

UInflightState::UInflightState()
{
	GetInflightNodeSparse()->NodeTitle = LOCTEXT("NodeTitle_State", "State");
}

void UInflightState::OnActivated_Implementation()
{
	UE_LOG(LogInflightGraph, Log, TEXT("State becoming active: %s"), *StateName)

	const APlayerController* Controller = GetInflightGraph()->GetActivePawn()->GetController<APlayerController>();
	if (IsValid(Controller))
	{
		auto&& EnhancedSubsystem = Controller->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

		if (IsValid(EnhancedSubsystem))
		{
			for (auto&& Mapping : Mappings)
			{
				EnhancedSubsystem->AddMappingContext(Mapping, 0);
			}
		}
	}

	for (auto&& Node : GetLinkedNodes())
	{
		if (!IsValid(Node)) continue;

		Node->AddActivationTrigger(this);
	}

	EventOnActivated.Broadcast();
}

void UInflightState::OnDeactivated_Implementation()
{
	UE_LOG(LogInflightGraph, Log, TEXT("State ending active: %s"), *StateName)

	for (auto&& Node : GetLinkedNodes())
	{
		if (!IsValid(Node)) continue;

		Node->RemoveActivationTrigger(this);
	}

	const APlayerController* Controller = GetInflightGraph()->GetActivePawn()->GetController<APlayerController>();
	if (IsValid(Controller))
	{
		auto&& EnhancedSubsystem = Controller->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

		if (IsValid(EnhancedSubsystem))
		{
			for (auto&& Mapping : Mappings)
			{
				EnhancedSubsystem->RemoveMappingContext(Mapping);
			}
		}
	}

	EventOnDeactivated.Broadcast();
}

void UInflightState::OnTriggered_Implementation(const FInputActionValue& ActionValue)
{
	if (!GetInflightGraph()->SetActiveState(this))
	{
		UE_LOG(LogInflightGraph, Warning, TEXT("State \"%s\" failed to set as active"), *StateName)
	}

	EventOnTriggered.Broadcast();
}

FString UInflightState::GetStateName() const
{
	if (StateName.IsEmpty())
	{
		return "<BLANK>";
	}
	return StateName;
}

FText UInflightState::GetStateTitle() const
{
	if (StateTitle.IsEmpty())
	{
		return FText::AsCultureInvariant("<BLANK>");
	}
	return StateTitle;
}

#undef LOCTEXT_NAMESPACE
