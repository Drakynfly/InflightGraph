// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightAction_GraphFunc.h"
#include "InflightGraph.h"

void UInflightAction_GraphFunc::OnTriggered_Implementation()
{
	Super::OnTriggered_Implementation();

	FSimpleDelegate Func;
	Func.BindUFunction(GetGraph(), FunctionName);
	Func.Execute();
}