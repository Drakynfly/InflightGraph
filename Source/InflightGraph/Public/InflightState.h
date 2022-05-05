// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InflightGraphNodeBase.h"
#include "InflightState.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class INFLIGHTGRAPH_API UInflightState : public UInflightGraphNodeBase
{
	GENERATED_BODY()

	virtual void OnSetup_Implementation() override;
	virtual void OnTriggered_Implementation() override;
	virtual void OnActivated_Implementation() override;
	virtual void OnDeactivated_Implementation() override;
};