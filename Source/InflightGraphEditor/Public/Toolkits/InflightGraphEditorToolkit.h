// Copyright (c) 2018 Jhonny Hueller
#pragma once

#include "Toolkits/AssetEditorToolkit.h"
#include "Misc/NotifyHook.h"
#include "GraphEditor.h"
#include "IDetailsView.h"

class UInflightGraph;

/**
 *
 */
class FInflightGraphEditorToolkit : public FAssetEditorToolkit, public FNotifyHook
{
public:
	FInflightGraphEditorToolkit();
	virtual ~FInflightGraphEditorToolkit() override;

	// Inherited via FAssetEditorToolkit
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void SaveAsset_Execute() override;

	virtual void InitGraphAssetEditor(const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost, UInflightGraph* InGraph);
	virtual void BlueprintCompiled();
private:

	static const FName DetailsTabId;
	static const FName GraphTabId;

	FGraphPanelSelectionSet GetSelectedNodes() const;
	TSharedRef<SDockTab> HandleTabManagerSpawnTabDetails(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> HandleTabManagerSpawnTabGraph(const FSpawnTabArgs& Args);
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

	TObjectPtr<UInflightGraph> GraphAsset;
	TSharedPtr<SGraphEditor> EdGraphEditor;
	TSharedPtr<IDetailsView> DetailsWidget;

	TSharedPtr<FUICommandList> GraphEditorCommands;
};