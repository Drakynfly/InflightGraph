// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

namespace Inflight::Pins
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Activation)
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Trigger)

	static const FName OnWake(TEXT("OnWake"));
	static const FName Triggered(TEXT("Triggered"));
}
