// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InflightActionBase.h"
#include "InflightAction_GraphFunc.generated.h"

/**
 *
 */
UCLASS()
class INFLIGHTGRAPH_API UInflightAction_GraphFunc : public UInflightActionBase
{
	GENERATED_BODY()

public:
	virtual void OnTriggered_Implementation() override;

	UPROPERTY()
	FName FunctionName;
};