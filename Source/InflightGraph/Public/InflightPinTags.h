// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "Model/HeartGraphPinTag.h"

// Pin tags for Inflight Nodes
struct FInflightPinTags : public FGameplayTagNativeAdder
{
	FORCEINLINE static const FInflightPinTags& Get()
	{
		return InflightPinTags;
	}

	virtual void AddTags() override;

	FHeartGraphPinTag Activation;
	FHeartGraphPinTag Trigger;

private:
	static FInflightPinTags InflightPinTags;
};

namespace Inflight::Pins
{
	static const FName OnWake(TEXT("OnWake"));
	static const FName Triggered(TEXT("Triggered"));
}
