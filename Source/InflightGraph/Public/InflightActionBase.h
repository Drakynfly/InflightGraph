// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightGraphNodeBase.h"
#include "InflightActionBase.generated.h"

/**
 * Actions are triggerable events that fire one-off abilities.
 */
UCLASS(Abstract, Blueprintable)
class INFLIGHTGRAPH_API UInflightActionBase : public UInflightGraphNodeBase
{
	GENERATED_BODY()

public:
	virtual void OnSetup_Implementation() override;
	virtual void OnTriggered_Implementation() override;
	virtual void OnActivated_Implementation() override;
	virtual void OnDeactivated_Implementation() override;
};