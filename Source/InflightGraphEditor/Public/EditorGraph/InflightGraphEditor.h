// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "InflightGraphEditor.generated.h"

class UInflightGraph;

/**
 *
 */
UCLASS()
class UInflightGraphEditor : public UEdGraph
{
	GENERATED_BODY()

public:
	virtual void SaveGraph();
	virtual void ClearOldLinks();
	virtual void LinkAssetNodes();
	virtual void RefreshNodes();
	virtual UInflightGraph* GetGraphAsset();
};