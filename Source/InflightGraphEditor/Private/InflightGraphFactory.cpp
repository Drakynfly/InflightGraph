// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraphFactory.h"
#include "InflightGraph.h"
#include "ClassViewerModule.h"
#include "ClassViewerFilter.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Kismet2/SClassPickerDialog.h"

#define LOCTEXT_NAMESPACE "InflightGraphFactory"

class FAssetClassParentFilter : public IClassViewerFilter
{
public:
	FAssetClassParentFilter()
		: DisallowedClassFlags(CLASS_None), bDisallowBlueprintBase(false)
	{}

	/** All children of these classes will be included unless filtered out by another setting. */
	TSet< const UClass* > AllowedChildrenOfClasses;

	/** Disallowed class flags. */
	EClassFlags DisallowedClassFlags;

	/** Disallow blueprint base classes. */
	bool bDisallowBlueprintBase;

	virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
	{
		const bool bAllowed = !InClass->HasAnyClassFlags(DisallowedClassFlags)
			&& InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InClass) != EFilterReturn::Failed;

		if (bAllowed && bDisallowBlueprintBase)
		{
			if (FKismetEditorUtilities::CanCreateBlueprintOfClass(InClass))
			{
				return false;
			}
		}

		return bAllowed;
	}

	virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef< const IUnloadedBlueprintData > InUnloadedClassData, TSharedRef< FClassViewerFilterFuncs > InFilterFuncs) override
	{
		if (bDisallowBlueprintBase)
		{
			return false;
		}

		return !InUnloadedClassData->HasAnyClassFlags(DisallowedClassFlags)
			&& InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InUnloadedClassData) != EFilterReturn::Failed;
	}
};


UInflightGraphFactory::UInflightGraphFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UInflightGraph::StaticClass();
}

UInflightGraphFactory::~UInflightGraphFactory()
{

}

bool UInflightGraphFactory::ConfigureProperties()
{
	// nullptr the InflightGraphClass so we can check for selection
	InflightGraphClass = nullptr;

	// Load the class viewer module to display a class picker
	FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

	// Fill in options
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;

	const TSharedRef<FAssetClassParentFilter> Filter = MakeShared<FAssetClassParentFilter>();
	Options.ClassFilters.Add(Filter);

	Filter->DisallowedClassFlags = CLASS_Abstract | CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_HideDropDown;
	Filter->AllowedChildrenOfClasses.Add(UInflightGraph::StaticClass());

	const FText TitleText = LOCTEXT("CreateInflightGraphAssetOptions", "Pick Generic Graph Class");
	UClass* ChosenClass = nullptr;
	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, UInflightGraph::StaticClass());

	if (bPressedOk)
	{
		InflightGraphClass = ChosenClass;
	}

	return bPressedOk;
}

UObject* UInflightGraphFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	if (InflightGraphClass != nullptr)
	{
		return NewObject<UInflightGraph>(InParent, InflightGraphClass, Name, Flags | RF_Transactional);
	}
	else
	{
		check(Class->IsChildOf(UInflightGraph::StaticClass()));
		return NewObject<UObject>(InParent, Class, Name, Flags | RF_Transactional);
	}

}

#undef LOCTEXT_NAMESPACE