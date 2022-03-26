// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "EditorGraph/InflightGraphEditor.h"
#include "EdGraph/EdGraphPin.h"
#include "Nodes/InflightGraphNode.h"
#include "EditorGraph/EditorNodes/InflightEditorGraphNode.h"
#include "Utility/InflightGraph_Log.h"
#include "Graphs/InflightGraph.h"

void UInflightGraphEditor::SaveGraph()
{
	LinkAssetNodes();
}

void UInflightGraphEditor::ClearOldLinks()
{
	for (UEdGraphNode* EditorNode : Nodes)
	{
		if (const UInflightEditorGraphNode* EdNode = Cast<UInflightEditorGraphNode>(EditorNode))
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
		if (UInflightEditorGraphNode* EdNode = Cast<UInflightEditorGraphNode>(EditorNode))
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
			if (UInflightEditorGraphNode* InflightNode = Cast<UInflightEditorGraphNode>(Node))
			{
				InflightNode->UpdateVisualNode();
			}
		}
	}
}

UInflightGraphBlueprint* UInflightGraphEditor::GetGraphBlueprint()
{
	return Cast<UInflightGraphBlueprint>(GetOuter());
}