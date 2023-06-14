// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightAction_OwningFunc.h"

#include "InflightGraph.h"

void UInflightAction_OwningFunc::OnTriggered_Implementation(const FInputActionValue& ActionValue)
{
	FSimpleDelegate Func;
	Func.BindUFunction(GetInflightGraph()->GetActivePawn(), FunctionName);
	Func.Execute();
}
