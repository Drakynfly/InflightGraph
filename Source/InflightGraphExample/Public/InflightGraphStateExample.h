// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InflightGraphState.h"
#include "InflightGraphStateExample.generated.h"

struct FInputActionValue;

/**
 *
 */
UCLASS()
class INFLIGHTGRAPHEXAMPLE_API UInflightGraphStateExample : public UInflightGraphState
{
	GENERATED_BODY()

	virtual void OnSetup_Implementation() override;
	virtual void OnActivated_Implementation() override;

public:
	void TextEvent(const FInputActionValue& ActionValue);
};