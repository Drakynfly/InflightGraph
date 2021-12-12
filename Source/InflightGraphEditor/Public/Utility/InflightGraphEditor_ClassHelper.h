// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

#include "InflightGraphEditor_ClassHelper.generated.h"

/**
 *
 */
USTRUCT()
struct FInflightGraphEditor_ClassData
{
	GENERATED_BODY()

	FInflightGraphEditor_ClassData() {}
	FInflightGraphEditor_ClassData(UClass* InClass, const FString& InDeprecatedMessage);
	FInflightGraphEditor_ClassData(const FString& InAssetName, const FString& InGeneratedClassPackage, const FString& InClassName, UClass* InClass);

	FString ToString() const;
	FString GetClassName() const;
	FText GetCategory() const;
	FString GetDisplayName() const;
	UClass* GetClass(bool bSilent = false);
	bool IsAbstract() const;

	FORCEINLINE bool IsBlueprint() const { return AssetName.Len() > 0; }
	FORCEINLINE bool IsDeprecated() const { return DeprecatedMessage.Len() > 0; }
	FORCEINLINE FString GetDeprecatedMessage() const { return DeprecatedMessage; }
	FORCEINLINE FString GetPackageName() const { return GeneratedClassPackage; }

	/** set when child class masked this one out (e.g. always use game specific class instead of engine one) */
	bool IsHidden = false;

	/** set when class wants to hide parent class from selection (just one class up hierarchy) */
	bool HideParent = false;

private:

	/** pointer to uclass */
	TWeakObjectPtr<UClass> Class;

	/** path to class if it's not loaded yet */
	UPROPERTY()
	FString AssetName;

	UPROPERTY()
	FString GeneratedClassPackage;

	/** resolved name of class from asset data */
	UPROPERTY()
	FString ClassName;

	/** User-defined category for this class */
	UPROPERTY()
	FText Category;

	/** message for deprecated class */
	FString DeprecatedMessage;
};

struct FInflightGraphEditor_ClassNode
{
	FInflightGraphEditor_ClassData Data;
	FString ParentClassName;

	TSharedPtr<FInflightGraphEditor_ClassNode> ParentNode;
	TArray<TSharedPtr<FInflightGraphEditor_ClassNode>> SubNodes;

	void AddUniqueSubNode(TSharedPtr<FInflightGraphEditor_ClassNode> SubNode);
};

struct FInflightGraphEditor_ClassHelper
{
public:
	DECLARE_MULTICAST_DELEGATE(FOnPackageListUpdated);

	FInflightGraphEditor_ClassHelper(UClass* InRootClass);
	~FInflightGraphEditor_ClassHelper();

	void GatherClasses(const UClass* BaseClass, TArray<FInflightGraphEditor_ClassData>& AvailableClasses);
	static FString GetDeprecationMessage(const UClass* Class);

	void OnAssetAdded(const struct FAssetData& AssetData);
	void OnAssetRemoved(const struct FAssetData& AssetData);
	void InvalidateCache();
	void OnReloadComplete(EReloadCompleteReason Reason);

	static void AddUnknownClass(const FInflightGraphEditor_ClassData& ClassData);
	static bool IsClassKnown(const FInflightGraphEditor_ClassData& ClassData);
	static FOnPackageListUpdated OnPackageListUpdated;

	static int32 GetObservedBlueprintClassCount(const UClass* BaseNativeClass);
	static void AddObservedBlueprintClasses(UClass* BaseNativeClass);
	void UpdateAvailableBlueprintClasses();

private:

	UClass* RootNodeClass;
	TSharedPtr<FInflightGraphEditor_ClassNode> RootNode;
	static TArray<FName> UnknownPackages;
	static TMap<UClass*, int32> BlueprintClassCount;

	TSharedPtr<FInflightGraphEditor_ClassNode> CreateClassDataNode(const struct FAssetData& AssetData);
	TSharedPtr<FInflightGraphEditor_ClassNode> FindBaseClassNode(TSharedPtr<FInflightGraphEditor_ClassNode> Node, const FString& ClassName);
	void FindAllSubClasses(TSharedPtr<FInflightGraphEditor_ClassNode> Node, TArray<FInflightGraphEditor_ClassData>& AvailableClasses);

	UClass* FindAssetClass(const FString& GeneratedClassPackage, const FString& AssetName);
	void BuildClassGraph();
	void AddClassGraphChildren(TSharedPtr<FInflightGraphEditor_ClassNode> Node, TArray<TSharedPtr<FInflightGraphEditor_ClassNode> >& NodeList);

	bool IsHidingClass(UClass* Class);
	bool IsHidingParentClass(UClass* Class);
	bool IsPackageSaved(FName PackageName);
};