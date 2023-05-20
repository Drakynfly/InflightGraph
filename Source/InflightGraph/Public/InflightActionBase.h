// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightNodeBase.h"
#include "InflightActionBase.generated.h"

/**
 * Actions fire one-off events.
 */
UCLASS(Abstract, Blueprintable)
class INFLIGHTGRAPH_API UInflightActionBase : public UInflightNodeBase
{
	GENERATED_BODY()

protected:
};
