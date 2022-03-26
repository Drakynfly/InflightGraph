// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "Factories/Factory.h"
#include "InflightGraphBlueprintFactory.generated.h"

class UInflightGraph;

UCLASS()
class UInflightGraphBlueprintFactory : public UFactory
{
	GENERATED_BODY()

protected:
	UInflightGraphBlueprintFactory();
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

public:
	// The parent class of the created blueprint
	UPROPERTY(EditAnywhere, Category = "Inflight Graph Blueprint Factory")
	TSubclassOf<UInflightGraph> ParentClass;
};