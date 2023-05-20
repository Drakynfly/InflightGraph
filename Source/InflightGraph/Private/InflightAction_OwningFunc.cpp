// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightAction_OwningFunc.h"

#include "InflightGraph.h"

void UInflightAction_OwningFunc::OnTriggered_Implementation()
{
	FSimpleDelegate Func;
	Func.BindUFunction(GetOuterUInflightGraph()->GetActivePawn(), FunctionName);
	Func.Execute();
}
