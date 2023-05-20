// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "InflightBlueprintFunctionLibrary.generated.h"

class UInflightGraph;

/**
 *
 */
UCLASS()
class INFLIGHTGRAPH_API UInflightBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Uses an Inflight Graph Asset to create a runtime copy, and initialized the copy to the root state.
	// If a valid input component is provided, the new graph will immediately activate;
	UFUNCTION(BlueprintCallable, Category = "Inflight Utils", meta = (DeterminesOutputType = "InflightAsset"))
	static UInflightGraph* StartInflightGraph(ACharacter* Owner, UInflightGraph* InflightAsset, AController* Controller);

	UFUNCTION(BlueprintCallable, Category = "Inflight Utils")
	static void EndInflightGraph(UInflightGraph* InflightInstance);
};