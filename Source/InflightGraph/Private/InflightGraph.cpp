// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraph.h"

#define LOCTEXT_NAMESPACE "InflightGraph"

UInflightGraph::UInflightGraph()
{
}

int32 UInflightGraph::GetLevelNum() const
{
	int32 Level = 0;
	TArray<UInflightGraphNode*> CurrLevelNodes = RootNodes;
	TArray<UInflightGraphNode*> NextLevelNodes;

	while (CurrLevelNodes.Num() != 0)
	{
		for (int32 i = 0; i < CurrLevelNodes.Num(); ++i)
		{
			UInflightGraphNode* Node = CurrLevelNodes[i];
			check(Node != nullptr);

			for (int32 j = 0; j < Node->GetChildrenNodes().Num(); ++j)
			{
				NextLevelNodes.Add(Node->GetChildrenNodes()[j]);
			}
		}

		CurrLevelNodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++Level;
	}

	return Level;
}

void UInflightGraph::GetNodesByLevel(int32 Level, TArray<UInflightGraphNode*>& Nodes)
{
	int32 CurrLevel = 0;
	TArray<UInflightGraphNode*> NextLevelNodes;

	Nodes = RootNodes;

	while (Nodes.Num() != 0)
	{
		if (CurrLevel == Level)
			break;

		for (int32 i = 0; i < Nodes.Num(); ++i)
		{
			UInflightGraphNode* Node = Nodes[i];
			check(Node != nullptr);

			for (int32 j = 0; j < Node->GetChildrenNodes().Num(); ++j)
			{
				NextLevelNodes.Add(Node->GetChildrenNodes()[j]);
			}
		}

		Nodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++CurrLevel;
	}
}

void UInflightGraph::ClearGraph()
{
	RootNodes.Empty();
	AllNodes.Empty();
}

#undef LOCTEXT_NAMESPACE