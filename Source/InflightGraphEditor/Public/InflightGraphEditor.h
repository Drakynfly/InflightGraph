// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#include "IAssetTools.h"

DECLARE_LOG_CATEGORY_EXTERN(LogInflightGraphEditor, Log, All);

class FInflightGraphEditor : public IModuleInterface
{
public:
	FInflightGraphEditor();

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static FInflightGraphEditor& Get()
	{
		return FModuleManager::LoadModuleChecked<FInflightGraphEditor>("InflightGraphEditor");
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("InflightGraphEditor");
	}

private:
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

private:
	TArray< TSharedPtr<IAssetTypeActions> > CreatedAssetTypeActions;
};