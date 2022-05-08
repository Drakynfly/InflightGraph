// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "EnhancedInputComponent.h"
#include "InflightGraphNodeBase.h"
#include "InputAction.h"
#include "InflightGraph.generated.h"

class UInflightState;

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

	UInflightGraphNodeBase* AddNode(TSubclassOf<UInflightGraphNodeBase> NodeClass, const FString& Name);

	template <typename TInflightGraphNodeClass>
	TInflightGraphNodeClass* AddNode(const FString& Name)
	{
		return Cast<TInflightGraphNodeClass>(AddNode(TInflightGraphNodeClass::StaticClass(), Name));
	}

	UInflightLinkBase* CreateLink(TSubclassOf<UInflightLinkBase> LinkClass, const FString& Name);

	template <typename TInflightLinkNodeClass>
	TInflightLinkNodeClass* CreateLink(const FString& Name)
	{
		return Cast<TInflightLinkNodeClass>(CreateLink(TInflightLinkNodeClass::StaticClass(), Name));
	}

	/** Link two nodes with a new link instance of the specified class */
	UInflightLinkBase* LinkNodes(TSubclassOf<UInflightLinkBase> LinkClass, const FString& Name, UInflightGraphNodeBase* NodeA, UInflightGraphNodeBase* NodeB);

	/** Link two nodes with the provided link instance */
	void LinkNodes(UInflightLinkBase* LinkObject, UInflightGraphNodeBase* NodeA, UInflightGraphNodeBase* NodeB);

	template <typename TInflightLinkNodeClass>
	TInflightLinkNodeClass* LinkNodes(UInflightGraphNodeBase* NodeA, UInflightGraphNodeBase* NodeB)
	{
		return Cast<TInflightLinkNodeClass>(LinkNodes(TInflightLinkNodeClass::StaticClass(), NodeA, NodeB));
	}


	void RegisterInputBinding(const FName Trigger);
#endif

	virtual void RebuildGraph() {}

	virtual void OnActivated();

	virtual void OnDeactivated();

	UFUNCTION(BlueprintCallable, Category = "Inflight Graph Editor", meta = (DeterminesOutputType = "NodeClass"), meta = (DisplayName = "Add Node"))
	UInflightGraphNodeBase* K2_AddNode(UPARAM(meta = (AllowAbstract = "false")) TSubclassOf<UInflightGraphNodeBase> NodeClass, FString Name);

	// Try to mark this object instance as a ActiveGraph.
	bool TryActivate(ACharacter* Owner, UEnhancedInputComponent* InInputComponent);

	void Deactivate();

	// Switch the active state. Will return true if when the NewActiveState has been successfully activated, or false
	// otherwise.
	bool SetActiveState(UInflightState* NewActiveState);

	UEnhancedInputComponent* GetInputComponent() const { return InputComponent; }

	UInputAction* GetRegisteredAction(FName BindingName) const;

private:
	UInflightGraphNodeBase* FindNodeByNameImpl(const FString& Name);

public:

	template <typename TInflightGraphNodeClass = UInflightGraphNodeBase>
	TInflightGraphNodeClass* FindNodeByName(const FString& Name)
	{
		return Cast<TInflightGraphNodeClass>(FindNodeByNameImpl(Name));
	}

	UFUNCTION(BlueprintCallable, Category = "Inflight Graph", meta = (DeterminesOutputType = Class))
	UInflightGraphNodeBase* FindNodeByName(UPARAM(meta = (AllowAbstract = "false")) TSubclassOf<UInflightGraphNodeBase> Class, const FString& Name);

private:
#if WITH_EDITOR
	UFUNCTION()
	TArray<FString> GetStatesList();
#endif

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inflight Graph")
	TObjectPtr<UInflightState> RootNode;

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
	UPROPERTY(BlueprintReadOnly, Category = "Inflight Graph|Runtime")
	bool ActiveGraph = false;

	UPROPERTY(BlueprintReadOnly, Category = "Inflight Graph|Runtime")
	ACharacter* ActiveCharacter = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Inflight Graph|Runtime")
	TObjectPtr<UInflightState> ActiveState;

	UPROPERTY(BlueprintReadOnly, Category = "Inflight Graph|Runtime")
	TObjectPtr<UEnhancedInputComponent> InputComponent = nullptr;
};