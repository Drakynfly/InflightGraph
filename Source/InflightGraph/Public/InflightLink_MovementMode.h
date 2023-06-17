// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightLinkBase.h"
#include "InflightLink_MovementMode.generated.h"

/**
 *
 */
UCLASS()
class INFLIGHTGRAPH_API UInflightLink_MovementMode : public UInflightLinkBase
{
	GENERATED_BODY()

protected:
	virtual void OnActivated_Implementation() override;
	virtual void OnDeactivated_Implementation() override;

	UFUNCTION()
	void ModeTrigger(ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);

	void CheckMovementMode();

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Inflight Link")
	TEnumAsByte<EMovementMode> ListeningMode;
};