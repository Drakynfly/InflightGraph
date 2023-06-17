// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightLink_MovementMode.h"

#include "InflightGraph.h"
#include "InflightGraphModule.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UInflightLink_MovementMode::OnActivated_Implementation()
{
	Super::OnActivated_Implementation();

	UE_LOG(LogInflightGraph, Log, TEXT("Movement mode change link \"%s\" Activated"), *GetName())

	if (ACharacter* Character = Cast<ACharacter>(GetInflightGraph()->GetActivePawn()))
	{
		Character->MovementModeChangedDelegate.AddDynamic(this, &UInflightLink_MovementMode::ModeTrigger);

		CheckMovementMode();
	}
	else
	{
		UE_LOG(LogInflightGraph, Error, TEXT("Movement mode change link unable to find ACharacter outer!"))
	}
}

void UInflightLink_MovementMode::OnDeactivated_Implementation()
{
	Super::OnDeactivated_Implementation();

	if (ACharacter* Character = Cast<ACharacter>(GetInflightGraph()->GetActivePawn()))
	{
		Character->MovementModeChangedDelegate.RemoveAll(this);
	}
}

// ReSharper disable once CppParameterMayBeConstPtrOrRef
void UInflightLink_MovementMode::ModeTrigger(ACharacter* Character, EMovementMode PrevMovementMode,
                                             uint8 PreviousCustomMode)
{
	CheckMovementMode();
}

void UInflightLink_MovementMode::CheckMovementMode()
{
	if (const ACharacter* Character = Cast<ACharacter>(GetInflightGraph()->GetActivePawn()))
	{
		if (ListeningMode == Cast<UCharacterMovementComponent>(Character->GetMovementComponent())->MovementMode)
		{
			UE_LOG(LogInflightGraph, Log, TEXT("Movement mode change link \"%s\" ListeningMode detected"), *GetName())
			Trigger(FInputActionValue());
		}
	}
}
