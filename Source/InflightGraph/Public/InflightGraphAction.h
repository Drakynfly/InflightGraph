// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InflightGraphNodeBase.h"
#include "InflightGraphAction.generated.h"

/**
 * Actions are triggerable events that fire one-off abilities.
 */
UCLASS(Abstract, Blueprintable)
class INFLIGHTGRAPH_API UInflightGraphAction : public UInflightGraphNodeBase
{
	GENERATED_BODY()

public:
	virtual void OnSetup_Implementation() override;
	virtual void OnActivated_Implementation() override;
	virtual void OnDeactivated_Implementation() override;
};