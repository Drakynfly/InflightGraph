// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightAction_OwningFunc.h"
#include "InflightGraph.h"

void UInflightAction_OwningFunc::OnTriggered_Implementation()
{
	Super::OnTriggered_Implementation();

	FSimpleDelegate Func;
	Func.BindUFunction(GetGraph()->GetTypedOuter<AActor>(), FunctionName);
	Func.Execute();
}