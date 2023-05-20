// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightBlueprintFunctionLibrary.h"
#include "InflightGraph.h"
#include "GameFramework/Character.h"

UInflightGraph* UInflightBlueprintFunctionLibrary::StartInflightGraph(ACharacter* Owner, UInflightGraph* InflightAsset, AController* Controller)
{
	if (IsValid(Owner) && IsValid(InflightAsset))
	{
		// Copy the date asset object into a new instance that can be modified at runtime.
		UInflightGraph* LiveGraph = DuplicateObject(InflightAsset, Owner);

		if (IsValid(LiveGraph))
		{
			if (IsValid(Controller))
			{
				LiveGraph->TryActivate(Owner, Controller);
			}

			return LiveGraph;
		}
	}

	return nullptr;
}

void UInflightBlueprintFunctionLibrary::EndInflightGraph(UInflightGraph* InflightInstance)
{
	if (IsValid(InflightInstance))
	{
		InflightInstance->Deactivate();
	}
}