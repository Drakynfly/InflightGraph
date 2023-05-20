// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InputTriggers.h"
#include "InflightInputBinding.generated.h"

USTRUCT()
struct FInflightInputBinding
{
	GENERATED_BODY()

	UPROPERTY()
	ETriggerEvent Trigger = ETriggerEvent::None;

	UPROPERTY()
	FName FunctionName;
};