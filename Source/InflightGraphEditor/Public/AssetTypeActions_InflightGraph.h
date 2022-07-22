// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "AssetTypeActions_Base.h"

class INFLIGHTGRAPHEDITOR_API FAssetTypeActions_InflightGraph : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_InflightGraph(EAssetTypeCategories::Type InAssetCategory);

	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;

private:
	EAssetTypeCategories::Type MyAssetCategory;
};