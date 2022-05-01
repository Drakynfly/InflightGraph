// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightBlueprintFunctionLibrary.h"

#include "EnhancedInputSubsystems.h"

UInflightGraph* UInflightBlueprintFunctionLibrary::StartInflightGraph(UObject* Owner, UInflightGraph* InflightAsset, UEnhancedInputComponent* InputComponent)
{
	if (IsValid(InflightAsset))
	{
		// Copy the asset into a new object.
		UInflightGraph* LiveGraph = NewObject<UInflightGraph>(Owner, InflightAsset->GetClass(), NAME_None, RF_NoFlags, InflightAsset);

		if (IsValid(LiveGraph))
		{
			if (IsValid(InputComponent))
			{
				LiveGraph->TryActivate(InputComponent);
			}

			return LiveGraph;
		}
	}

	return nullptr;
}