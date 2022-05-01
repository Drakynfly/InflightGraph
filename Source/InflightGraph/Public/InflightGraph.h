// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "EnhancedInputComponent.h"
#include "InflightGraphNodeBase.h"
#include "InputAction.h"
#include "InflightGraph.generated.h"

class UInflightGraphState;

/**
 * Inflight graph is a state machine for locomotion.
 * It handles input and dynamically triggers Actions and transitions to States based on rules defined by node objects.
 *
 * Currently, there is no Graph Editor for Inflight. The workflow is to create a c++ class that implements the states,
 * links, and actions, then create a BP asset for that class, configure it as required, and use that asset as input for
 * functionality using InflightGraphs.
 */
UCLASS(Blueprintable, Abstract)
class INFLIGHTGRAPH_API UInflightGraph : public UObject
{
	GENERATED_BODY()

public:
	UInflightGraph();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;

	void ExecRebuildGraph();

	void ClearGraph();

	UInflightGraphNodeBase* AddNode(TSubclassOf<UInflightGraphNodeBase>, FString Name);

	template <typename TInflightGraphNode>
	TInflightGraphNode* AddNode(FString Name)
	{
		return Cast<TInflightGraphNode>(AddNode(TInflightGraphNode::StaticClass(), Name));
	}


	void RegisterInputBinding(const FName Trigger);
#endif

	UFUNCTION(BlueprintNativeEvent)
	void RebuildGraph();

	UFUNCTION(BlueprintCallable, Category = "Inflight Graph Editor", meta = (DeterminesOutputType = "NodeClass"), meta = (DisplayName = "Add Node"))
	UInflightGraphNodeBase* K2_AddNode(UPARAM(meta = (AllowAbstract = "false")) TSubclassOf<UInflightGraphNodeBase> NodeClass, FString Name);

	virtual void OnActivated();

	// Try to mark this object instance as a ActiveGraph.
	bool TryActivate(UEnhancedInputComponent* InInputComponent);

	UFUNCTION(BlueprintImplementableEvent, Category = "Inflight Graph", meta = (DisplayName = "OnActivated"))
	void K2_OnActivated();

	UEnhancedInputComponent* GetInputComponent() const { return InputComponent; }

	UInputAction* GetRegisteredAction(FName BindingName) const;

	UInflightGraphNodeBase* FindNodeByName(const FString& Name);

private:
#if WITH_EDITOR
	UFUNCTION()
	TArray<FString> GetStatesList();
#endif

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inflight Graph")
	TObjectPtr<UInflightGraphState> RootNode;

	UPROPERTY(BlueprintReadOnly, Category = "Inflight Graph")
	TArray<TObjectPtr<UInflightGraphNodeBase>> AllNodes;

#if WITH_EDITORONLY_DATA
	///////////////////////////////////////////////////////////////
	///					BLUEPRINT CONFIG						///
	///		These members are edited by BP children assets		///
	///////////////////////////////////////////////////////////////

	/** The state that newly created Inflight Machines initialize to. */
	UPROPERTY(EditAnywhere, Category = "Inflight Graph Config", meta = (GetOptions = "GetStatesList"))
	FString StartingState;
#endif

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Inflight Graph Config")
	TMap<FName, TObjectPtr<UInputAction>> RegisteredInputNames;

#if WITH_EDITORONLY_DATA
private:
	TMap<FName, TObjectPtr<UInputAction>> RegisteredInputNames_REBUILDDATA;
#endif


	///////////////////////////////////////////////////////////////
	///					RUNTIME DATA							///
	///		Runtime-only variables for tracking state			///
	///////////////////////////////////////////////////////////////

protected:
	// Tracks if this object is a live graph, and contains a locomotion state, or is just a prototype instance.
	UPROPERTY(BlueprintReadOnly)
	bool ActiveGraph = false;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UEnhancedInputComponent> InputComponent = nullptr;
};