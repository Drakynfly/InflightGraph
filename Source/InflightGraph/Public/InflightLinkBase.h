// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightNodeBase.h"
#include "InflightLinkBase.generated.h"

class UInflightGraph;

/**
 *
 */
UCLASS(Abstract, BlueprintType)
class INFLIGHTGRAPH_API UInflightLinkBase : public UInflightNodeBase
{
	GENERATED_BODY()

protected:
	virtual void OnActivated_Implementation() override;
	virtual void OnDeactivated_Implementation() override;
	virtual void OnTriggered_Implementation() override;
};
