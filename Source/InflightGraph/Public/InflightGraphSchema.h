// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "ModelView/HeartGraphSchema.h"
#include "InflightGraphSchema.generated.h"

/**
 *
 */
UCLASS()
class INFLIGHTGRAPH_API UInflightGraphSchema : public UHeartGraphSchema
{
	GENERATED_BODY()

public:
	UInflightGraphSchema();

	virtual FHeartConnectPinsResponse CanPinsConnect_Implementation(const UHeartGraph* Graph, FHeartGraphPinReference PinA, FHeartGraphPinReference PinB) const override;
};
