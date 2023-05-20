// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "Model/HeartGraphNode.h"
#include "InflightGraphNodeBase.generated.h"

class UInflightLinkBase;
class UInflightNodeBase;

/**
 *
 */
UCLASS(Abstract)
class UInflightGraphNodeBase : public UHeartGraphNode
{
	GENERATED_BODY()

public:
	virtual FText GetNodeTitle_Implementation(const UObject* Node, EHeartNodeNameContext Context) const override;

#if WITH_EDITOR
	void AddParentLink(UInflightLinkBase* Node, UInflightNodeBase* Link);

	void AddChildLink(UInflightLinkBase* Node, UInflightNodeBase* Link);
#endif
};
