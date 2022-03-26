// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

struct FInflightGraphEditor_ClassHelper;

class FInflightEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual TSharedPtr<FInflightGraphEditor_ClassHelper> GetHelper();

private:
	TSharedPtr<FInflightGraphEditor_ClassHelper> NodeHelper;
};