// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogInflightGraph, Log, All);

/**
 * The public interface to this module
 */
class FInflightGraph : public IModuleInterface
{

public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};