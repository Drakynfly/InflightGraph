// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "ModelView/Actions/HeartGraphAction.h"
#include "CompileInflightGraph.generated.h"

/**
 *
 */
UCLASS()
class INFLIGHTGRAPH_API UCompileInflightGraph : public UHeartGraphAction
{
	GENERATED_BODY()

protected:
	virtual void ExecuteOnGraph(UHeartGraph* Graph, const FHeartInputActivation& Activation, UObject* ContextObject) override;
};
