// Fill out your copyright notice in the Description page of Project Settings.

#include "Graphs/InflightGraph.h"
#include "Nodes/InflightGraphNode.h"

#define LOCTEXT_NAMESPACE "InflightGraph"

UInflightGraph::UInflightGraph()
{
#if WITH_EDITORONLY_DATA
	EdGraph = nullptr;
#endif
}

void UInflightGraph::InitGraph(UObject* ParentObject)
{
    Owner = ParentObject;
}

#if WITH_EDITORONLY_DATA
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

#undef LOCTEXT_NAMESPACE