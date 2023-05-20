// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightGraphNodeBase.h"
#include "InflightGraphNode_Action.generated.h"

class UInflightActionBase;

/**
 *
 */
UCLASS()
class INFLIGHTGRAPH_API UInflightGraphNode_Action : public UInflightGraphNodeBase
{
	GENERATED_BODY()

public:
	virtual FText GetNodeCategory_Implementation(const UObject* Node) const override;
	virtual FLinearColor GetNodeTitleColor_Implementation(const UObject* Node) override;

	UFUNCTION(BlueprintCallable, Category = "Inflight|Graph|Actions")
	UInflightActionBase* GetActionNode() const;
};
