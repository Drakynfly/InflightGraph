// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightGraphNodeBase.h"

#include "InflightGraphNode_Link.generated.h"

class UInflightLinkBase;

/**
 *
 */
UCLASS()
class INFLIGHTGRAPH_API UInflightGraphNode_Link : public UInflightGraphNodeBase
{
	GENERATED_BODY()

public:
	virtual FText GetNodeCategory_Implementation(const UObject* Node) const override;
	virtual FLinearColor GetNodeTitleColor_Implementation(const UObject* Node) override;

	UFUNCTION(BlueprintCallable, Category = "Inflight|Graph|Links")
	UInflightLinkBase* GetLinkNode() const;
};
