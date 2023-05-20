// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraph.h"
#include "InflightGraphModule.h"
#include "InflightGraphSchema.h"
#include "InflightState.h"

#include "EnhancedInputComponent.h"
#include "InflightGraphNode_State.h"

UInflightGraph::UInflightGraph()
{
#if WITH_EDITORONLY_DATA
	EditorData.GraphTypeName = FText::FromString("Inflight");
	EditorData.CanCreateAssetFromFactory = true;
#endif
}

TSubclassOf<UHeartGraphSchema> UInflightGraph::GetSchemaClass_Implementation() const
{
	return UInflightGraphSchema::StaticClass();
}

bool UInflightGraph::TryActivate(APawn* Owner, AController* Controller)
{
	if (!IsAsset() &&
		!IsTemplate() &&
		!ActiveGraph &&
		IsValid(RootState) &&
		IsValid(Owner) &&
		IsValid(Controller))
	{
		ActiveGraph = true;
		ActivePawn = Owner;

		InputComponent = Controller->InputComponent;
		SetupInputComponent();

		ActivePawn->ReceiveControllerChangedDelegate.AddDynamic(this, &ThisClass::OnControllerChanged);

		SetActiveState(RootState);

		UE_LOG(LogInflightGraph, Log, TEXT("Inflight Graph %s activated! Bound to %s"), *GetName(), *Controller->GetName())
	}

	return ActiveGraph;
}

void UInflightGraph::Deactivate()
{
	if (ensure(ActiveGraph))
	{
		SetActiveState(nullptr);

		ActiveGraph = false;
		ActivePawn = nullptr;
		InputComponent = nullptr;

		UE_LOG(LogInflightGraph, Log, TEXT("Inflight Graph %s deactivated!"), *GetName())
	}
}

bool UInflightGraph::SetActiveState(UInflightState* NewActiveState)
{
	if (ActiveState == NewActiveState)
	{
		// Early-out nonsense call.
		return false;
	}

	if (IsValid(ActiveState))
	{
		ActiveState->RemoveActivationTrigger(this);
		ActiveState = nullptr;
	}

	// Ensure the state is a valid state that we own.
	if (IsValid(NewActiveState) && NewActiveState->GetOuter() == this)
	{
		ActiveState = NewActiveState;
		NewActiveState->AddActivationTrigger(this);
		return true;
	}

	return false;
}

void UInflightGraph::SetupInputComponent()
{
	if (auto&& EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		/*
		// For some reason if we try to pass "this" directly into the BindAction call it tries to compile the
		// templated version that expects a function pointer instead of a FName, so we need to do this . . .
		UObject* Target = this;

		for (const FInflightInputBinding& InputBinding : AutomaticInputBindings)
		{
			if (const UInputAction* Action = GetRegisteredAction(InputBinding.FunctionName))
			{
				uint32 NewBinding = EnhancedInput->BindAction(Action,
							InputBinding.Trigger, Target, InputBinding.FunctionName).GetHandle();

				BindingHandles.Add(NewBinding);
			}
		}
		*/
	}
}

void UInflightGraph::OnControllerChanged(APawn* Pawn, AController* OldController, AController* NewController)
{
	// @todo we need to rebind anything that was bound to the old inputcomponent

	InputComponent = nullptr;

	if (NewController)
	{
		InputComponent = NewController->InputComponent;
	}

	SetupInputComponent();
}

#if WITH_EDITOR
TArray<FString> UInflightGraph::GetRootNodeOptions() const
{
	TArray<FString> StateNames;

	TArray<UHeartGraphNode*> AllNodes;
	GetNodeArray(AllNodes);
	for (auto&& Node : AllNodes)
	{
		if (UInflightState* AsState = Node->GetNodeObject<UInflightState>())
		{
			StateNames.AddUnique(AsState->GetStateName());
		}
	}

	return StateNames;
}

void UInflightGraph::SetRootState(UInflightState* State)
{
	RootState = State;
}
#endif