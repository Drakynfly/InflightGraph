// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "EditorGraph/InflightGraphEditor.h"
#include "EdGraph/EdGraphPin.h"
#include "Nodes/InflightGraphNode.h"
#include "EditorGraph/EditorNodes/InflightGraphNodeEditor.h"
#include "Utility/InflightGraph_Log.h"
#include "Graphs/InflightGraph.h"

bool UInflightGraphEditor::IsNameUnique(const FText & InName)
{
	bool bUnique = true;
	for (UEdGraphNode* Node : Nodes)
	{
		const UInflightGraphNodeEditor* PNode = Cast<UInflightGraphNodeEditor>(Node);
		FText NodeName = PNode->GetEdNodeName();
		if (bUnique==true && !NodeName.IsEmpty())
		{
			if (NodeName.EqualToCaseIgnored(InName))
			{
				INFLIGHTGRAPH_WARNING("I found another node with the same name: %s.", *NodeName.ToString());
				bUnique = false;
			}
		}
	}
	return bUnique;
}

void UInflightGraphEditor::SaveGraph()
{
	LinkAssetNodes();
	MapNamedNodes();
}

void UInflightGraphEditor::ClearOldLinks()
{
	for (UEdGraphNode* EditorNode : Nodes)
	{
		if (const UInflightGraphNodeEditor* EdNode = Cast<UInflightGraphNodeEditor>(EditorNode))
		{
			EdNode->AssetNode->ClearLinks();
		}
	}
}

void UInflightGraphEditor::LinkAssetNodes()
{
	ClearOldLinks();
	INFLIGHTGRAPH_LOG("Starting to link all asset nodes from the editor graph links.");
	for (UEdGraphNode* EditorNode : Nodes)
	{
		if (UInflightGraphNodeEditor* EdNode = Cast<UInflightGraphNodeEditor>(EditorNode))
		{
			if (UInflightGraphNode* NodeAsset = EdNode->AssetNode)
			{
				TArray<UEdGraphPin*>& EdPinsParent = EdNode->Pins;
				TArray<UEdGraphNode*>Children;

				for (UEdGraphPin* Pin : EdPinsParent)
				{
					//Take only the output pins
					if (Pin->Direction == EGPD_Output)
					{

						TArray<UEdGraphPin*>& EdPinsChildren = Pin->LinkedTo;
						for (const UEdGraphPin* LinkedPin : EdPinsChildren)
						{
							Children.Add(LinkedPin->GetOwningNode());
						}
					}
				}

                EdNode->SaveNodesAsChildren(Children);
			}
			else
			{
				INFLIGHTGRAPH_ERROR("There is no asset node linked to this editor node.");
			}
		}
		else
		{
			INFLIGHTGRAPH_WARNING("An unknow EdNode has been found.");
		}
	}

}

void UInflightGraphEditor::RefreshNodes()
{
	for (UEdGraphNode* Node : Nodes)
	{
		if (Node)
		{
			if (UInflightGraphNodeEditor* InflightNode = Cast<UInflightGraphNodeEditor>(Node))
			{
				InflightNode->UpdateVisualNode();
			}
		}
	}
}

void UInflightGraphEditor::MapNamedNodes()
{
	UInflightGraph* Graph = GetGraphAsset();
	Graph->NamedNodes.Empty();
    Graph->NodesNames.Empty();

	for (UEdGraphNode* Node : Nodes)
	{
		if (const UInflightGraphNodeEditor* InflightNode = Cast<UInflightGraphNodeEditor>(Node))
		{
			FText Name = InflightNode->GetEdNodeName();
            if (!Name.IsEmpty())
            {
                Graph->NamedNodes.Add(Name.ToString(), InflightNode->AssetNode);
                Graph->NodesNames.Add(InflightNode->AssetNode, Name.ToString());
            }
		}
	}
}

UInflightGraph* UInflightGraphEditor::GetGraphAsset()
{
	return Cast<UInflightGraph>(GetOuter());
}