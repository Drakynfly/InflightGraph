// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "EditorGraph/SlateWidgets/SInflightGraphNode.h"
#include "Slate.h"
#include "GraphEditorSettings.h"
#include "SGraphPin.h"
#include "SCommentBubble.h"
#include "EditorGraph/EditorNodes/InflightEditorGraphNode.h"
#include "EditorGraph/SlateWidgets/SInflightGraphPin.h"
#include "Utility/InflightGraph_Log.h"

#define LOCTEXT_NAMESPACE "SInflightGraphNode"

class UInflightEditorGraphNode;

void SInflightGraphNode::Construct(const FArguments& InArgs, UEdGraphNode* InNode)
{
	GraphNode = InNode;
	UpdateGraphNode();
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SInflightGraphNode::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	const TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);
	TSharedPtr<SErrorText> ErrorText;

	const FLinearColor NodeFullColor = GraphNode->GetNodeBodyTintColor();
	const FLinearColor NodeHalfColor = NodeFullColor/2;

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);

	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
			.Padding(FMargin(1.f, 5.0f))
			.BorderBackgroundColor(NodeFullColor)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SAssignNew(LeftNodeBox, SVerticalBox)
				]
				+ SHorizontalBox::Slot()
				.HAlign(HAlign_Fill)
				[
					SNew(SBorder)
                    .BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
                    .Padding(FMargin(5.0f))
                    .BorderBackgroundColor(NodeHalfColor)
                    [
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.HAlign(HAlign_Center)
						.AutoHeight()
						[
							SAssignNew(NodeHeader, STextBlock)
						]
						+ SVerticalBox::Slot()
						.HAlign(HAlign_Center)
						.AutoHeight()
						[
							SAssignNew(InlineEditableText, SInlineEditableTextBlock)
							.Style(FEditorStyle::Get(), "Graph.StateNode.NodeTitleInlineEditableText")
							.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
							.IsReadOnly(this, &SInflightGraphNode::IsNameReadOnly)
							.OnVerifyTextChanged(this, &SInflightGraphNode::OnVerifyNameTextChanged)
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							NodeTitle.ToSharedRef()
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SAssignNew(ContentWidget, SBox)
						]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SAssignNew(ErrorText, SErrorText)
							.BackgroundColor(this, &SInflightGraphNode::GetErrorColor)
							.ToolTipText(this, &SInflightGraphNode::GetErrorMsgToolTip)
						]
                    ]
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				[
					SAssignNew(RightNodeBox, SVerticalBox)
				]
			]
		];

	TSharedPtr<SCommentBubble> CommentBubble;
	const FSlateColor CommentColor = GetDefault<UGraphEditorSettings>()->DefaultCommentNodeTitleColor;

	SAssignNew(CommentBubble, SCommentBubble)
		.GraphNode(GraphNode)
		.Text(this, &SGraphNode::GetNodeComment)
		.OnTextCommitted(this, &SGraphNode::OnCommentTextCommitted)
		.ColorAndOpacity(CommentColor)
		.AllowPinning(true)
		.EnableTitleBarBubble(true)
		.EnableBubbleCtrls(true)
		.GraphLOD(this, &SGraphNode::GetCurrentLOD)
		.IsGraphNodeHovered(this, &SGraphNode::IsHovered);

	GetOrAddSlot(ENodeZone::TopCenter)
		.SlotOffset(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetOffset))
		.SlotSize(TAttribute<FVector2D>(CommentBubble.Get(), &SCommentBubble::GetSize))
		.AllowScaling(TAttribute<bool>(CommentBubble.Get(), &SCommentBubble::IsScalingAllowed))
		.VAlign(VAlign_Top)
		[
			CommentBubble.ToSharedRef()
		];

	UpdateErrorInfo();
	ErrorReporting = ErrorText;
	ErrorReporting->SetError(ErrorMsg);

	CreatePinWidgets();
	CreateContent();
    CreateHeader();
}

void SInflightGraphNode::CreatePinWidgets()
{
	UInflightEditorGraphNode* EdNode = CastChecked<UInflightEditorGraphNode>(GraphNode);
	for (int32 i = 0; i < EdNode->Pins.Num(); ++i)
	{
		UEdGraphPin* Pin = EdNode->Pins[i];
		if (!Pin->bHidden)
		{
			TSharedPtr<SGraphPin>NewPin = SNew(SInflightGraphPin, Pin);
			AddPin(NewPin.ToSharedRef());
		}
	}
}

void SInflightGraphNode::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));
	if (PinToAdd->GetDirection() == EEdGraphPinDirection::EGPD_Input)
	{
		LeftNodeBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.FillHeight(1.0f)
			.Padding(0.f, 0.0f)
			[
				PinToAdd
			];
		InputPins.Add(PinToAdd);
	}
	else
	{
		RightNodeBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.FillHeight(1.0f)
			.Padding(0.f, 0.0f)
			[
				PinToAdd
			];
		OutputPins.Add(PinToAdd);
	}
}

void SInflightGraphNode::CreateContent()
{
	UInflightEditorGraphNode* Node = Cast<UInflightEditorGraphNode>(GraphNode);

	ContentWidget->SetContent(Node->GetContentWidget().ToSharedRef());
	ContentWidget->SetMinDesiredWidth(200.f);
}

void SInflightGraphNode::CreateHeader()
{
    NodeHeader.Get()->SetText(GraphNode->GetNodeTitle(ENodeTitleType::MenuTitle));

    if (const UInflightEditorGraphNode* UEdNode = CastChecked<UInflightEditorGraphNode>(GraphNode))
    {
    	NodeHeader.Get()->SetVisibility(EVisibility::Visible);

		//NodeHeader.Get()->SetVisibility(UEdNode->GetEdNodeName().IsEmpty() ? EVisibility::Collapsed : EVisibility::Visible);
    }
    else
    {
		INFLIGHTGRAPH_ERROR("An error occurred when creating the slate node headers");
    }
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE