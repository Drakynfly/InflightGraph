// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "CompileInflightGraph.h"

#include "InflightGraph.h"
#include "InflightGraphNodeBase.h"
#include "InflightNodeBase.h"
#include "InflightStartNode.h"

void UCompileInflightGraph::ExecuteOnGraph(UHeartGraph* Graph, const FHeartInputActivation& Activation,
										   UObject* ContextObject)
{
	UInflightGraph* InflightGraph = Cast<UInflightGraph>(Graph);

	if (!ensure(IsValid(InflightGraph)))
	{
		return;
	}

	TArray<UHeartGraphNode*> AllNodes;
	InflightGraph->GetNodeArray(AllNodes);

	for (auto&& Node : AllNodes)
	{
		auto&& InflightHeartNode = Cast<UInflightGraphNodeBase>(Node);
		if (!ensure(InflightHeartNode)) continue;
		auto&& InflightNode = InflightHeartNode->GetNodeObject<UInflightNodeBase>();
		if (!ensure(InflightNode)) continue;

		TSet<TObjectPtr<UInflightNodeBase>> LinkedNodes;

		TArray<FHeartPinGuid> OutputPins = InflightHeartNode->GetOutputPins();

		for (const FHeartPinGuid OutputPin : OutputPins)
		{
			const FHeartGraphPinConnections& Inputs = InflightHeartNode->GetLinks(OutputPin);

			for (const FHeartGraphPinReference& Link : Inputs.Links)
			{
				auto&& LinkedGraphNode = InflightGraph->GetNode(Link.NodeGuid);
				if (!LinkedGraphNode) continue;
				auto&& LinkedNode = LinkedGraphNode->GetNodeObject<UInflightNodeBase>();
				if (!ensure(LinkedNode)) continue;

				LinkedNodes.Add(LinkedNode);
			}
		}

		InflightNode->SetLinkedNodes(LinkedNodes);

		if (UInflightStartNode* StartNode = Cast<UInflightStartNode>(InflightNode))
		{
			InflightGraph->StartNode = StartNode;
		}
	}
}
