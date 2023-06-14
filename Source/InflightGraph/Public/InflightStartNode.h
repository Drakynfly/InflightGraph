// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightNodeBase.h"
#include "InflightStartNode.generated.h"

/**
 *
 */
UCLASS()
class INFLIGHTGRAPH_API UInflightStartNode : public UInflightNodeBase
{
	GENERATED_BODY()

public:
	virtual void OnActivated_Implementation() override;
};
