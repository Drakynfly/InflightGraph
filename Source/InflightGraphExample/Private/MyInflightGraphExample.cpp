// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "MyInflightGraphExample.h"
#include "InflightGraphStateExample.h"

void UMyInflightGraphExample::RebuildGraph_Implementation()
{
#if WITH_EDITOR

	AddNode(UInflightGraphStateExample::StaticClass(), "CoreInputs");

#endif
}