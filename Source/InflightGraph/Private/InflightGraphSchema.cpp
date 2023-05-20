// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraphSchema.h"
#include "CompileInflightGraph.h"

UInflightGraphSchema::UInflightGraphSchema()
{
#if WITH_EDITORONLY_DATA
	FlushNodesForRuntime = true;
	EditorPreSaveAction = UCompileInflightGraph::StaticClass();
#endif
}
