// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InflightGraphNodeBase.h"
#include "InflightGraphState.generated.h"

/**
 *
 */
UCLASS(Abstract, Blueprintable)
class INFLIGHTGRAPH_API UInflightGraphState : public UInflightGraphNodeBase
{
	GENERATED_BODY()

	virtual void OnSetup_Implementation() override;
	virtual void OnActivated_Implementation() override;
	virtual void OnDeactivated_Implementation() override;
};