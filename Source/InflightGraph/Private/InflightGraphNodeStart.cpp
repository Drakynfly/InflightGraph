// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraphNodeStart.h"

#include "InflightPinTags.h"

UInflightGraphNodeStart::UInflightGraphNodeStart()
{
	FHeartGraphPinDesc PinDesc;
	PinDesc.Name = Inflight::Pins::OnWake;
	PinDesc.Direction = EHeartPinDirection::Output;
	PinDesc.Tag = FHeartGraphPinTag::TryConvert(Inflight::Pins::Activation);
	GetHeartGraphNodeSparseClassData()->DefaultPins = { PinDesc };
}
