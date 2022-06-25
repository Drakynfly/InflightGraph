// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraph.h"

#include "EnhancedInputComponent.h"
#include "InflightActionBase.h"
#include "InflightLinkBase.h"
#include "InflightGraphModule.h"
#include "InflightState.h"
#include "UObject/ObjectSaveContext.h"

#define LOCTEXT_NAMESPACE "InflightGraph"

UInflightGraph::UInflightGraph()
{
}

#if WITH_EDITOR
void UInflightGraph::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UObject::PostEditChangeProperty(PropertyChangedEvent);


}

void UInflightGraph::PreSave(const FObjectPreSaveContext SaveContext)
{
	if (IsAsset())
	{
		ExecRebuildGraph();
	}

	UObject::PreSave(SaveContext);
}

void UInflightGraph::ExecRebuildGraph()
{
	// Cache Rebuild Data
	RegisteredInputNames_REBUILDDATA = RegisteredInputNames;

	// Empty all permanent caches.
	ClearGraph();

	// Hook for child class to construct all nodes and links.
	RebuildGraph();

	// Auto-fill cached values for rebuilt keys.
	for (auto PreviouslyRegisteredInput : RegisteredInputNames_REBUILDDATA)
	{
		if (RegisteredInputNames.Contains(PreviouslyRegisteredInput.Key))
		{
			RegisteredInputNames.Add(PreviouslyRegisteredInput);
		}
	}

	RegisteredInputNames_REBUILDDATA.Empty();
}

void UInflightGraph::ClearGraph()
{
	AllNodes.Empty();
	RootNode = nullptr;
	RegisteredInputNames.Empty();
}

UInflightGraphNodeBase* UInflightGraph::AddNode(const TSubclassOf<UInflightGraphNodeBase> NodeClass, const FString& Name)
{
	UInflightGraphNodeBase* NewNode = NewObject<UInflightGraphNodeBase>(this, NodeClass);

	NewNode->Setup(this, Name);

	AllNodes.Add(NewNode);

	return NewNode;
}

UInflightLinkBase* UInflightGraph::CreateLink(const TSubclassOf<UInflightLinkBase> LinkClass, const FString& Name)
{
	UInflightLinkBase* NewLink = NewObject<UInflightLinkBase>(this, LinkClass);

	NewLink->SetName(Name);

	return NewLink;
}

UInflightLinkBase* UInflightGraph::LinkNodes(const TSubclassOf<UInflightLinkBase> LinkClass, const FString& Name, UInflightGraphNodeBase* NodeA, UInflightGraphNodeBase* NodeB)
{
	UInflightLinkBase* NewLink = CreateLink(LinkClass, Name);
	LinkNodes(NewLink, NodeA, NodeB);
	return NewLink;
}

void UInflightGraph::LinkNodes(UInflightLinkBase* LinkObject, UInflightGraphNodeBase* NodeA,
	UInflightGraphNodeBase* NodeB)
{
	LinkObject->Setup(this, NodeA, NodeB);
	NodeA->AddChildLink(NodeB, LinkObject);
	NodeB->AddParentLink(NodeA, LinkObject);
}

void UInflightGraph::SetRootNode(UInflightState* Node)
{
	RootNode = Node;
}

void UInflightGraph::RegisterInputBinding(const FName BindingName)
{
	RegisteredInputNames.Add(BindingName);
}

void UInflightGraph::RegisterInputBinding(const ETriggerEvent Trigger, const FName Function)
{
	RegisteredInputNames.Add(Function);
	AutomaticInputBindings.Add({Trigger, Function});
}
#endif

void UInflightGraph::OnActivated()
{
	if (IsValid(InputComponent))
	{
		if (UEnhancedInputComponent* const EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
		{
			for (const FInflightInputBinding& InputBinding : AutomaticInputBindings)
			{
				// For some reason if we try to pass "this" directly into the BindAction call it tries to compile the
				// templated version that expects a function pointer instead of a FName, so we need to do this . . .
				UObject* Target = this;

				if (const UInputAction* Action = GetRegisteredAction(InputBinding.FunctionName))
				{
					uint32 NewBinding = EnhancedInput->BindAction(Action,
								InputBinding.Trigger, Target, InputBinding.FunctionName).GetHandle();

					BindingHandles.Add(NewBinding);
				}
			}
		}
	}
}

void UInflightGraph::OnDeactivated()
{
	if (UEnhancedInputComponent* const EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		for (const uint32 Handle : BindingHandles)
		{
			EnhancedInput->RemoveBindingByHandle(Handle);
		}
	}
}

UInflightGraphNodeBase* UInflightGraph::K2_AddNode(const TSubclassOf<UInflightGraphNodeBase> NodeClass, const FString Name)
{
#if WITH_EDITOR
	return AddNode(NodeClass, Name);
#else
	return nullptr;
#endif
}

bool UInflightGraph::TryActivate(APawn* Owner, UEnhancedInputComponent* InInputComponent)
{
	//InflightState* StartingNode = DetermineStartingNode();

	if (!IsAsset() && !ActiveGraph && IsValid(RootNode) && IsValid(InInputComponent))
	{
		ActiveGraph = true;
		ActivePawn = Owner;
		InputComponent = InInputComponent;
		//SetActiveState(StartingNode);
		SetActiveState(RootNode);
		OnActivated();

		UE_LOG(LogInflightGraph, Log, TEXT("Inflight Graph %s activated! Bound to %s"), *GetName(), *InputComponent->GetName())
	}

	return ActiveGraph;
}

void UInflightGraph::Deactivate()
{
	if (!IsAsset() && ActiveGraph)
	{
		SetActiveState(nullptr);
		OnDeactivated();

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

UInputAction* UInflightGraph::GetRegisteredAction(const FName BindingName) const
{
	if (!RegisteredInputNames.Contains(BindingName)) return nullptr;
	return RegisteredInputNames.FindChecked(BindingName);
}

UInflightGraphNodeBase* UInflightGraph::FindNodeByNameImpl(const FString& Name)
{
	for (const TObjectPtr<UInflightGraphNodeBase>& Node : AllNodes)
	{
		if (Node && Node->GetNodeName() == Name)
		{
			return Node;
		}
	}

	return nullptr;
}

UInflightGraphNodeBase* UInflightGraph::FindNodeByName(TSubclassOf<UInflightGraphNodeBase> Class, const FString& Name)
{
	return FindNodeByNameImpl(Name);
}

void UInflightGraph::RemoteTriggerAction(const FString& Name)
{
	const auto NamedNode = FindNodeByName<UInflightActionBase>(Name);

	if (IsValid(NamedNode) && NamedNode->IsActive())
	{
		NamedNode->Trigger();
	}
}

#if WITH_EDITOR
TArray<FString> UInflightGraph::GetStatesList()
{
	TArray<FString> States;

	for (const TObjectPtr<UInflightGraphNodeBase>& Node : AllNodes)
	{
		if (Node && Node->IsA<UInflightState>())
		{
			States.Add(Node->GetNodeName());
		}
	}

	if (States.IsEmpty())
	{
		return {FString("No States to select")};
	}

	return States;
}
#endif

#undef LOCTEXT_NAMESPACE