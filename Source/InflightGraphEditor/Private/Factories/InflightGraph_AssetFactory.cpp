// Fill out your copyright notice in the Description page of Project Settings.
#include "Factories/InflightGraph_AssetFactory.h"

#include "Graphs/InflightGraph.h"

UInflightGraph_AssetFactory::UInflightGraph_AssetFactory()
{
	SupportedClass = UInflightGraph::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UInflightGraph_AssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, const FName InName,
													   const EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UInflightGraph>(InParent, InClass, InName, Flags);
}