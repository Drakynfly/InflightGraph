// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "MyInflightGraphExample.h"
#include "InflightGraphAction_OwningFunc.h"
#include "InflightLinkBase.h"
#include "InflightLink_InputAction.h"
#include "InflightLink_MovementMode.h"
#include "InflightState.h"
#include "GameFramework/Character.h"

void UMyInflightGraphExample::RebuildGraph_Implementation()
{
#if WITH_EDITOR

	const auto WalkingState = AddNode<UInflightState>("Walking");
	const auto FlyingState = AddNode<UInflightState>("Flying");
	const auto FallingState = AddNode<UInflightState>("Falling");

	const auto WalkingToFallingAutoLink = CreateLink<UInflightLink_MovementMode>("WalkingToFallingAutoLink");
	WalkingToFallingAutoLink->ListeningMode = MOVE_Falling;
	LinkNodes(WalkingToFallingAutoLink, WalkingState, FallingState);

	const auto FallingToWalkingAutoLink = CreateLink<UInflightLink_MovementMode>("FallingToWalkingAutoLink");
	FallingToWalkingAutoLink->ListeningMode = MOVE_Walking;
	LinkNodes(FallingToWalkingAutoLink, FallingState, WalkingState);

	const auto JumpNode = AddNode<UInflightGraphAction_OwningFunc>("Jump");
	JumpNode->FunctionName = GET_FUNCTION_NAME_CHECKED(ACharacter, Jump);

	const auto JumpLink = CreateLink<UInflightLink_InputAction>("JumpAction");
	JumpLink->ActionBinding.LinkName = "JumpLink";
	JumpLink->ActionBinding.Trigger = ETriggerEvent::Triggered;

	LinkNodes(JumpLink, WalkingState, JumpNode);

	const auto JumpInAirLink = CreateLink<UInflightLink_InputAction>("TriggerFlightAction");
	JumpInAirLink->ActionBinding.LinkName = "JumpLink";
	JumpInAirLink->ActionBinding.Trigger = ETriggerEvent::Triggered;

	LinkNodes(JumpInAirLink, FallingState, FlyingState);

#endif
}