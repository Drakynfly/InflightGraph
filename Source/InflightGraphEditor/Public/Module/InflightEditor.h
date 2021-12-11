// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FInflightEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void StartNodeHelper();
	virtual TSharedPtr<struct FInflightGraphEditor_ClassHelper> GetHelper() { return NodeHelper; }

private:
	TSharedPtr<struct FInflightGraphEditor_ClassHelper> NodeHelper;
};