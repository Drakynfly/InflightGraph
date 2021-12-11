// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "InflightGraphEditor.generated.h"

/**
 *
 */
class UInflightGraph;

UCLASS()
class UInflightGraphEditor : public UEdGraph
{
	GENERATED_BODY()

public:
	virtual bool IsNameUnique(const FText& InName);
	virtual void SaveGraph();
	virtual void ClearOldLinks();
	virtual void LinkAssetNodes();
	virtual void RefreshNodes();
	virtual void MapNamedNodes();
	virtual UInflightGraph* GetGraphAsset();
};