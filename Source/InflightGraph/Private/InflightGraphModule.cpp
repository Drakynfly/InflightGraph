// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraphModule.h"

DEFINE_LOG_CATEGORY(LogInflightGraph)

IMPLEMENT_MODULE( FInflightGraph, InflightGraph )

void FInflightGraph::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}

void FInflightGraph::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}