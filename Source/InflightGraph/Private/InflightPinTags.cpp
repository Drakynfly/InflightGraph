// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightPinTags.h"

FInflightPinTags FInflightPinTags::InflightPinTags;

void FInflightPinTags::AddTags()
{
	Activation = FHeartGraphPinTag::AddNativeTag("Inflight.Activation");
	Trigger = FHeartGraphPinTag::AddNativeTag("Inflight.Trigger");
}
