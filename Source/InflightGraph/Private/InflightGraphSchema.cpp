// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraphSchema.h"
#include "CompileInflightGraph.h"
#include "Model/HeartGraph.h"
#include "Model/HeartGraphPinReference.h"

UInflightGraphSchema::UInflightGraphSchema()
{
#if WITH_EDITORONLY_DATA
	RunCanPinsConnectInEdGraph = true;
	FlushNodesForRuntime = true;
	EditorPreSaveAction = UCompileInflightGraph::StaticClass();
#endif
}

FHeartConnectPinsResponse UInflightGraphSchema::CanPinsConnect_Implementation(const UHeartGraph* Graph,
																			  const FHeartGraphPinReference PinA,
																			  const FHeartGraphPinReference PinB) const
{
	// All pin connections are allowable
	return FHeartConnectPinsResponse{EHeartCanConnectPinsResponse::Allow};
}