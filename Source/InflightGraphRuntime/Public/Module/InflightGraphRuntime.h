﻿// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FInflightGraphRuntimeModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};