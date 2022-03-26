// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "BlueprintEditor.h"
#include "GraphEditor.h"
#include "IDetailsView.h"

class UInflightGraphBlueprint;
class UInflightGraph;

/**
 *
 */
class FInflightGraphBlueprintEditor : public FBlueprintEditor
{
public:
	FInflightGraphBlueprintEditor();
	virtual ~FInflightGraphBlueprintEditor() override;

	virtual void InitInflightGraphBlueprintEditor(const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost, UInflightGraphBlueprint* InGraph);

	//~ Begin IToolkit Interface
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FGraphAppearanceInfo GetGraphAppearance(UEdGraph* InGraph) const override;
	//~ End IToolkit Interface


	// virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	// virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void SaveAsset_Execute() override;

	//virtual FActionMenuContent OnCreateGraphActionMenu(UEdGraph* InGraph, const FVector2D& InNodePosition, const TArray<UEdGraphPin*>& InDraggedPins, bool bAutoExpand, SGraphEditor::FActionMenuClosed InOnMenuClosed);


	virtual void BlueprintCompiled();
private:

	static const FName DetailsTabId;
	static const FName GraphTabId;

	void BindToolkitCommands();

	//Delegates
	void OnCommandSelectAllNodes();
	bool CanSelectAllNodes();

	void OnCommandCopy();
	bool CanCopyNodes();

	void OnCommandPaste();
	bool CanPasteNodes();

	void OnCommandCut();
	bool CanCutNodes();

	void OnCommandDuplicate();
	bool CanDuplicateNodes();

	void OnCommandDelete();
	bool CanDeleteNodes();

	TObjectPtr<UInflightGraphBlueprint> GraphBlueprint;
	TSharedPtr<SGraphEditor> EdGraphEditor;
	TSharedPtr<IDetailsView> DetailsWidget;

	TSharedPtr<FUICommandList> GraphEditorCommands;
};