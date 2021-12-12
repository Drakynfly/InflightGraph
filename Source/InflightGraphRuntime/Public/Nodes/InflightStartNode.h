// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "Nodes/InflightGraphNode.h"
#include "InflightStartNode.generated.h"

class UInflightStateNode;

/**
 *
 */
UCLASS(NotBlueprintable)
class INFLIGHTGRAPHRUNTIME_API UInflightStartNode : public UInflightGraphNode
{
	GENERATED_BODY()

	UInflightStartNode();

	virtual void LinkArgumentNodeAsChild(UInflightGraphNode* Child) override;

protected:
	virtual bool HasInputPins() const override { return false; }

public:
	UInflightStateNode* GetConnectedState() const { return ConnectedState; }

private:
	UPROPERTY()
	TObjectPtr<UInflightStateNode> ConnectedState;
};