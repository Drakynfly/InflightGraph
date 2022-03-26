// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "Graphs/InflightGraph.h"

#include "InflightGraphEditor/Public/AssetTypeActions/InflightGraph_AssetTypeActions.h"
#include "Nodes/InflightGraphNode.h"
#include "UObject/ObjectSaveContext.h"

#define LOCTEXT_NAMESPACE "InflightGraph"

#if WITH_EDITOR

void UInflightGraphBlueprint::SetStartNode(UInflightStartNode* StartingNode)
{
	StartNode = StartingNode;
}

void UInflightGraphBlueprint::AddNode(UInflightGraphNode* InNode)
{
	InNode->SetGraphBlueprint(this);
	InNode->Rename(nullptr, this);
	int32 Index = Nodes.Add(InNode);
}

void UInflightGraphBlueprint::RemoveNode(UInflightGraphNode* NodeToRemove)
{
	for (UInflightGraphNode* Node : Nodes)
	{
		Node->RemoveLinkedNode(NodeToRemove);
	}

	int32 Removed = Nodes.Remove(NodeToRemove);
}

void UInflightGraphBlueprint::SetInflightGraph(UEdGraph* EdGraph)
{
	InflightEditorGraph = EdGraph;
}
#endif

UInflightGraphBlueprint* UInflightGraphBlueprint::FindRootInflightGraphBlueprint(const UInflightGraphBlueprint* DerivedBlueprint)
{
	UInflightGraphBlueprint* ParentBP = nullptr;

	// Determine if there is an anim blueprint in the ancestry of this class
	for (UClass* ParentClass = DerivedBlueprint->ParentClass; ParentClass && (UObject::StaticClass() != ParentClass); ParentClass = ParentClass->GetSuperClass())
	{
		if (UInflightGraphBlueprint* TestBP = Cast<UInflightGraphBlueprint>(ParentClass->ClassGeneratedBy))
		{
			ParentBP = TestBP;
		}
	}

	return ParentBP;
}

UInflightGraphBlueprint* UInflightGraphBlueprint::GetParentInflightGraphBlueprint(const UInflightGraphBlueprint* DerivedBlueprint)
{
	UInflightGraphBlueprint* ParentBP = nullptr;
	UClass* ParentClass = DerivedBlueprint->ParentClass;

	if (UInflightGraphBlueprint* TestBP = Cast<UInflightGraphBlueprint>(ParentClass->ClassGeneratedBy))
	{
		ParentBP = TestBP;
	}

	return ParentBP;
}

UInflightGraph::UInflightGraph()
{
#if WITH_EDITORONLY_DATA
	EdGraph = nullptr;
#endif
}

void UInflightGraph::PreSave(const FObjectPreSaveContext SaveContext)
{
	if (StartNode == nullptr)
	{
		for (auto Node : Nodes)
		{
			if (Node.IsA(UInflightStartNode::StaticClass()))
			{
				StartNode = Cast<UInflightStartNode>(Node);
			}
		}
	}

	UObject::PreSave(SaveContext);
}

UInflightGraph* UInflightGraph::CreateInflightGraph(const TSubclassOf<UInflightGraph> Class, APawn* Agent, const bool BeginGraphAfterCreation)
{
	if (!IsValid(Class))
	{
		return nullptr;
	}

	UInflightGraph* NewGraph = NewObject<UInflightGraph>(Agent, Class);

	NewGraph->RunningAgent = Agent;

	if (BeginGraphAfterCreation)
	{
		NewGraph->BeginGraph();
	}

	return NewGraph;
}

void UInflightGraph::BeginGraph()
{
	if (UInflightStateNode* InitialState = Cast<UInflightStateNode>(StartNode->GetConnectedState()))
	{
		SwitchActiveState(InitialState);
	}
	else
	{
		UE_LOG(LogInflightGraph, Error, TEXT("No Initial State Connected!"))
	}
}

void UInflightGraph::SwitchActiveState(UInflightStateNode* NewState)
{
	if (ActiveStateNode == NewState)
	{
		UE_LOG(LogInflightGraph, Error, TEXT("Tried to set Active State to the state already Active!"))
		return;
	}

	if (ActiveStateNode)
	{
		ActiveStateNode->SetInactive();
	}

	ActiveStateNode = NewState;

	if (ActiveStateNode)
	{
		ActiveStateNode->SetActive();
	}
}

APawn* UInflightGraph::GetAgentTyped(const TSubclassOf<APawn> Type) const
{
	ensure(RunningAgent.IsA(Type));
	return RunningAgent;
}

#undef LOCTEXT_NAMESPACE