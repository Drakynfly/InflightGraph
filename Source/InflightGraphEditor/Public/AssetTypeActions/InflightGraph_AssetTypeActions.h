// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "AssetTypeActions/AssetTypeActions_Blueprint.h"

/**
 *
 */
class FInflightGraph_AssetTypeActions : public FAssetTypeActions_Blueprint
{
public:
	FInflightGraph_AssetTypeActions();

	// Inherited via FAssetTypeActions_Base
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

	virtual UFactory* GetFactoryForBlueprintType(UBlueprint* InBlueprint) const override;
};