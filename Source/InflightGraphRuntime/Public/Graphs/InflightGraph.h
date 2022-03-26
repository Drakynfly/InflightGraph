// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "Nodes/InflightStartNode.h"
#include "Nodes/InflightStateNode.h"
#include "InflightGraph.generated.h"

DECLARE_LOG_CATEGORY_CLASS(LogInflightGraph, Log, All)

/**
*
*/
UCLASS(BlueprintType)
class INFLIGHTGRAPHRUNTIME_API UInflightGraphBlueprint : public UBlueprint
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	// UBlueprint interface
	virtual bool SupportedByDefaultBlueprintFactory() const override { return false; }
	// End of UBlueprint interface

	template <class T>
	T* SpawnNodeInsideGraph(const TSubclassOf<UInflightGraphNode> InNodeClass)
	{
		T* NewNode = NewObject<T>(this, InNodeClass, NAME_None, RF_Transactional);
		AddNode(NewNode);
		return NewNode;
	}

	void SetStartNode(UInflightStartNode* StartingNode);
	virtual void AddNode(UInflightGraphNode* InNode);
	virtual void RemoveNode(UInflightGraphNode* NodeToRemove);

	void SetInflightGraph(UEdGraph* EdGraph);
#endif

public:
	static UInflightGraphBlueprint* FindRootInflightGraphBlueprint(const UInflightGraphBlueprint* DerivedBlueprint);

	static UInflightGraphBlueprint* GetParentInflightGraphBlueprint(const UInflightGraphBlueprint* DerivedBlueprint);

	/** The node to being state transition from */
	UPROPERTY(BlueprintReadOnly, Category = "Graph Data")
	TObjectPtr<UInflightStartNode> StartNode;

	/** The currently running state. */
	UPROPERTY(BlueprintReadOnly, Category = "Graph Data", Transient)
	TObjectPtr<UInflightStateNode> ActiveStateNode;

	UPROPERTY(BlueprintReadOnly, Category = "Graph Data")
	TArray<TObjectPtr<UInflightGraphNode>> Nodes;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	TObjectPtr<UEdGraph> InflightEditorGraph;
#endif
};

class UInflightGraphNode;

/**
 *
 */
UCLASS(Blueprintable, BlueprintType)
class INFLIGHTGRAPHRUNTIME_API UInflightGraph : public UObject
{
	GENERATED_BODY()

public:
	UInflightGraph();

#if WITH_EDITOR
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
#endif

	// @todo add a component that is placed on the actor, and calls this automatically
	UFUNCTION(BlueprintCallable, Category = "Inflight Graph")
	static UInflightGraph* CreateInflightGraph(TSubclassOf<UInflightGraph> Class, APawn* Agent, bool BeginGraphAfterCreation);

	UFUNCTION(BlueprintCallable, Category = "Inflight Graph")
	void BeginGraph();

	/** Allows for State Nodes to access the agent as a specific type quickly, without casting more than once. */
	template <class T>
	T* GetAgent() const
	{
		static T* CastAgentCache;

		if (RunningAgent == nullptr)
		{
			UE_LOG(LogInflightGraph, Warning, TEXT("Invalid Agent in Inflight Graph"))
			return nullptr;
		}

		if (CastAgentCache == nullptr)
		{
			CastAgentCache = Cast<T>(RunningAgent);
		}

		checkf(CastAgentCache, TEXT("GetAgent<T> called with "))
		return CastAgentCache;
	}

	void SwitchActiveState(UInflightStateNode* NewState);

	UFUNCTION(BlueprintPure, Category = "Inflight Graph", meta = (DeterminesOutputType = Type))
	APawn* GetAgentTyped(TSubclassOf<APawn> Type) const;

#if WITH_EDITORONLY_DATA
public:
	UPROPERTY()
	class UEdGraph* EdGraph;
#endif

protected:
	/** The node to being state transition from */
	UPROPERTY(BlueprintReadOnly, Category = "Graph Data")
	TObjectPtr<UInflightStartNode> StartNode;

	/** The currently running state. */
	UPROPERTY(BlueprintReadOnly, Category = "Graph Data", Transient)
	TObjectPtr<UInflightStateNode> ActiveStateNode;

	UPROPERTY(BlueprintReadOnly, Category = "Graph Data")
	TArray<TObjectPtr<UInflightGraphNode>> Nodes;

private:
	UPROPERTY()
	TObjectPtr<APawn> RunningAgent;
};