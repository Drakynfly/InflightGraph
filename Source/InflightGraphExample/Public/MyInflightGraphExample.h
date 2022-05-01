// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightGraph.h"
#include "MyInflightGraphExample.generated.h"

/**
 *
 */
UCLASS()
class INFLIGHTGRAPHEXAMPLE_API UMyInflightGraphExample : public UInflightGraph
{
	GENERATED_BODY()

	virtual void RebuildGraph_Implementation() override;
};