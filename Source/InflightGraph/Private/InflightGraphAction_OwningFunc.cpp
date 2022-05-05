// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraphAction_OwningFunc.h"
#include "InflightGraph.h"

void UInflightGraphAction_OwningFunc::OnTriggered_Implementation()
{
	Super::OnTriggered_Implementation();

	FName ActualFuncName = GetGraph()->GetTypedOuter<AActor>()->FindFunction(FunctionName)->GetFName();

	FSimpleDelegate Func;
	Func.BindUFunction(GetGraph()->GetTypedOuter<AActor>(), FunctionName);
	Func.Execute();
}

void UInflightGraphAction_OwningFunc::OnActivated_Implementation()
{
	Super::OnActivated_Implementation();
}