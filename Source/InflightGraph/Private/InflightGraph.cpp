// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraph.h"

#include "EnhancedInputComponent.h"
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

	if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UInflightGraph, StartingState))
	{
		ExecRebuildGraph();
	}
}

void UInflightGraph::PreSave(const FObjectPreSaveContext SaveContext)
{
	ExecRebuildGraph();
	UObject::PreSave(SaveContext);
}

void UInflightGraph::ExecRebuildGraph()
{
	// Cache Rebuild Data
	RegisteredInputNames_REBUILDDATA = RegisteredInputNames;

	// Empty all permanent caches.
	ClearGraph();

	// Allow BP to run RebuildGraph
	FEditorScriptExecutionGuard();
	RebuildGraph();

	// Select the root node from asset config
	RootNode = Cast<UInflightState>(FindNodeByName(StartingState));

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

void UInflightGraph::RegisterInputBinding(const FName Trigger)
{
	RegisteredInputNames.Add(Trigger);
}
#endif

void UInflightGraph::RebuildGraph_Implementation()
{
}

UInflightGraphNodeBase* UInflightGraph::K2_AddNode(const TSubclassOf<UInflightGraphNodeBase> NodeClass, const FString Name)
{
#if WITH_EDITOR
	return AddNode(NodeClass, Name);
#endif
}

void UInflightGraph::OnActivated()
{
	SetActiveState(RootNode);

	K2_OnActivated();
}

bool UInflightGraph::TryActivate(UEnhancedInputComponent* InInputComponent)
{
	if (!IsAsset() && !ActiveGraph && IsValid(RootNode) && IsValid(InInputComponent))
	{
		ActiveGraph = true;
		InputComponent = InInputComponent;

		UE_LOG(LogInflightGraph, Log, TEXT("Inflight Graph %s activated! Bound to %s"), *GetName(), *InputComponent->GetName())

		OnActivated();
	}

	return ActiveGraph;
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
		ActiveState->Deactivate();
		ActiveState = nullptr;
	}

	// Ensure the state is a valid state that we own.
	if (IsValid(NewActiveState) && NewActiveState->GetOuter() == this)
	{
		ActiveState = NewActiveState;
		NewActiveState->Activate();
		return true;
	}

	return false;
}

UInputAction* UInflightGraph::GetRegisteredAction(const FName BindingName) const
{
	return RegisteredInputNames.Find(BindingName)->Get();
}

UInflightGraphNodeBase* UInflightGraph::FindNodeByName(const FString& Name)
{
	for (const TObjectPtr<UInflightGraphNodeBase>& Node : AllNodes)
	{
		if (Node->GetNodeName() == Name)
		{
			return Node;
		}
	}

	return nullptr;
}

#if WITH_EDITOR
TArray<FString> UInflightGraph::GetStatesList()
{
	TArray<FString> States;

	for (const TObjectPtr<UInflightGraphNodeBase>& Node : AllNodes)
	{
		if (Node->IsA<UInflightState>())
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