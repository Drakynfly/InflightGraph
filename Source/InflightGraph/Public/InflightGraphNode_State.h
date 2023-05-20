// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightGraphNodeBase.h"

#include "InflightGraphNode_State.generated.h"

class UInflightState;

/**
 *
 */
UCLASS()
class INFLIGHTGRAPH_API UInflightGraphNode_State : public UInflightGraphNodeBase
{
	GENERATED_BODY()

public:
	virtual FText GetNodeTitle_Implementation(const UObject* Node, EHeartNodeNameContext Context) const override;
	virtual FText GetNodeCategory_Implementation(const UObject* Node) const override;
	virtual FLinearColor GetNodeTitleColor_Implementation(const UObject* Node) override;
	virtual void GetNodeMessages_Implementation(TArray<FHeartGraphNodeMessage>& Messages) const override;

	UFUNCTION(BlueprintCallable, Category = "Inflight|Graph|States")
	UInflightState* GetStateNode() const;
};
