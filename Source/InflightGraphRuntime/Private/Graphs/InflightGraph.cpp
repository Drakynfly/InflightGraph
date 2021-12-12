// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "Graphs/InflightGraph.h"
#include "Nodes/InflightGraphNode.h"
#include "UObject/ObjectSaveContext.h"

#define LOCTEXT_NAMESPACE "InflightGraph"

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

void UInflightGraph::InitGraph(APawn* Agent)
{
	checkf(Agent, TEXT("Don't pass in a null agent please."));

	RunningAgent = Agent;

	// @todo remove this eventually. right now inflight graphs are referenced as asset, which requires this reset
	if (ActiveStateNode)
	{
		ActiveStateNode->SetInactive();
		ActiveStateNode = nullptr;
	}

	if (UInflightStateNode* InitialState = Cast<UInflightStateNode>(StartNode->GetConnectedState()))
	{
		SwitchActiveState(InitialState);
	}
	else
	{
		UE_LOG(LogInflightGraph, Error, TEXT("No Initial State Connected!"))
	}
}

#if WITH_EDITORONLY_DATA

void UInflightGraph::SetStartNode(UInflightStartNode* StartingNode)
{
	StartNode = StartingNode;
}

void UInflightGraph::AddNode(UInflightGraphNode* InNode)
{
	InNode->SetGraph(this);
	InNode->Rename(nullptr, this);
	int32 Index = Nodes.Add(InNode);
}

void UInflightGraph::RemoveNode(UInflightGraphNode* NodeToRemove)
{
	for (UInflightGraphNode* Node : Nodes)
	{
		Node->RemoveLinkedNode(NodeToRemove);
	}

	int32 Removed = Nodes.Remove(NodeToRemove);
}
#endif

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