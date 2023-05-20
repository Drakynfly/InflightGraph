// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "Model/HeartGraph.h"
#include "InflightGraph.generated.h"

enum class ETriggerEvent : uint8;
struct FInflightInputBinding;
class UInflightNodeBase;
class UInputAction;
class UInflightState;
class UInflightLinkBase;

/**
 * InflightGraph is a state machine for player input.
 * It manages its own input bindings and dynamically triggers Actions and transitions to States based on rules
 * defined by Links.
 */
UCLASS()
class INFLIGHTGRAPH_API UInflightGraph : public UHeartGraph
{
	GENERATED_BODY()

	friend UInflightState;

public:
	UInflightGraph();

protected:
	//* Begin UHeartGraph interface
	virtual TSubclassOf<UHeartGraphSchema> GetSchemaClass_Implementation() const override;
	//* End UHeartGraph interface

public:
	// Try to mark this object instance as a ActiveGraph.
	bool TryActivate(APawn* Owner, AController* Controller);

	void Deactivate();

protected:
	// Switch the active state. Will return true if when the NewActiveState has been successfully activated, or false
	// otherwise. Should only be used by ourself or UInflightState.
	bool SetActiveState(UInflightState* NewActiveState);

public:
	template <typename TInputComponentClass = UInputComponent>
	TInputComponentClass* GetInputComponent() const { return Cast<TInputComponentClass>(InputComponent); }

	UFUNCTION(BlueprintCallable, Category = "Inflight|Runtime")
	APawn* GetActivePawn() const { return ActivePawn; }

	UFUNCTION(BlueprintCallable, Category = "Inflight|Runtime")
	UInflightState* GetActiveState() const { return ActiveState; }

private:
	void SetupInputComponent();

	UFUNCTION()
	void OnControllerChanged(APawn* Pawn, AController* OldController, AController* NewController);

#if WITH_EDITOR
	UFUNCTION()
	TArray<FString> GetRootNodeOptions() const;

public:
	void SetRootState(UInflightState* State);
	FString GetRootNode() const { return RootNode; }
#endif


	/**---------------------------------------------------------**/
	/*						CONFIG DATA							 */
	/*		Asset-level variables used to initialize graphs		 */
	/**---------------------------------------------------------**/
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inflight|Config")
	TObjectPtr<UInflightState> RootState;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "Inflight|Config", meta = (GetOptions = "GetRootNodeOptions"))
	FString RootNode;
#endif


	/**---------------------------------------------------------**/
	/*					RUNTIME DATA							 */
	/*		Runtime-only variables for tracking state			 */
	/**---------------------------------------------------------**/

protected:
	// Tracks if this object is a live graph, and contains a locomotion state, or is just a prototype instance.
	UPROPERTY(BlueprintReadOnly, Category = "Inflight|Runtime")
	bool ActiveGraph = false;

	UPROPERTY(BlueprintReadOnly, Category = "Inflight|Runtime")
	APawn* ActivePawn = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Inflight|Runtime")
	TObjectPtr<UInflightState> ActiveState;

	UPROPERTY(BlueprintReadOnly, Category = "Inflight|Runtime")
	TObjectPtr<UInputComponent> InputComponent = nullptr;
};
