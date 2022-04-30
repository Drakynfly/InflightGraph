// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "AssetTypeActions_InflightGraph.h"

#include "InflightGraph.h"

#define LOCTEXT_NAMESPACE "AssetTypeActions_InflightGraph"

FAssetTypeActions_InflightGraph::FAssetTypeActions_InflightGraph(const EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FText FAssetTypeActions_InflightGraph::GetName() const
{
	return LOCTEXT("FInflightGraphAssetTypeActionsName", "Inflight Graph");
}

FColor FAssetTypeActions_InflightGraph::GetTypeColor() const
{
	return FColor(50, 150, 200);
}

UClass* FAssetTypeActions_InflightGraph::GetSupportedClass() const
{
	return UInflightGraph::StaticClass();
}

uint32 FAssetTypeActions_InflightGraph::GetCategories()
{
	return MyAssetCategory;
}

//////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE