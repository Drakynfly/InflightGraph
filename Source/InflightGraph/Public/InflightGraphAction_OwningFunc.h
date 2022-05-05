// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InflightActionBase.h"
#include "InflightGraphAction_OwningFunc.generated.h"

/**
 * A Graph Action that calls a function on the graph's owning actor.
 */
UCLASS()
class INFLIGHTGRAPH_API UInflightGraphAction_OwningFunc : public UInflightActionBase
{
	GENERATED_BODY()

public:
	virtual void OnTriggered_Implementation() override;
	virtual void OnActivated_Implementation() override;

	UPROPERTY()
	FName FunctionName;
};