// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.


#include "InflightLink_MovementMode.h"
#include "InflightGraph.h"
#include "InflightGraphModule.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UInflightLink_MovementMode::OnActivated()
{
	Super::OnActivated();

	UE_LOG(LogInflightGraph, Log, TEXT("Movement mode change link \"%s\" Activated"), *Name)

	if (ACharacter* Character = Graph->GetTypedOuter<ACharacter>())
	{
		Character->MovementModeChangedDelegate.AddDynamic(this, &UInflightLink_MovementMode::ModeTrigger);
	}
	else
	{
		UE_LOG(LogInflightGraph, Error, TEXT("Movement mode change link unable to find ACharacter outer!"))
	}
}

void UInflightLink_MovementMode::OnDeactivated()
{
	Super::OnDeactivated();

	if (const auto Character = Graph->GetTypedOuter<ACharacter>())
	{
		Character->MovementModeChangedDelegate.RemoveAll(this);
	}
}

void UInflightLink_MovementMode::OnTriggered()
{
	Super::OnTriggered();

	if (IsValid(EndNode))
	{
		EndNode->Trigger();
	}
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void UInflightLink_MovementMode::ModeTrigger(ACharacter* Character, EMovementMode PrevMovementMode,
                                             uint8 PreviousCustomMode)
{
	if (ListeningMode == Cast<UCharacterMovementComponent>(Character->GetMovementComponent())->MovementMode)
	{
		UE_LOG(LogInflightGraph, Log, TEXT("Movement mode change link \"%s\" ListeningMode detected"), *Name)
		Trigger();
	}
}