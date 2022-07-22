// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "Factories/Factory.h"
#include "InflightGraph.h"
#include "InflightGraphFactory.generated.h"

UCLASS()
class INFLIGHTGRAPHEDITOR_API UInflightGraphFactory : public UFactory
{
	GENERATED_BODY()

public:
	UInflightGraphFactory();
	virtual ~UInflightGraphFactory();

	UPROPERTY(EditAnywhere, Category=DataAsset)
	TSubclassOf<UInflightGraph> InflightGraphClass;

	virtual bool ConfigureProperties() override;
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};