// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
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
	virtual void OnActivated() override;
	virtual void OnDeactivated() override;
	virtual void OnTriggered() override;

	UFUNCTION()
	void ModeTrigger(class ACharacter* Character, EMovementMode PrevMovementMode, uint8 PreviousCustomMode);

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Inflight Link")
	TEnumAsByte<EMovementMode> ListeningMode;
};