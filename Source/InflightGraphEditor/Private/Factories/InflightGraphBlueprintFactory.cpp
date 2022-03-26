// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "Factories/InflightGraphBlueprintFactory.h"
#include "EditorGraph/InflightEditorGraphSchema.h"
#include "EditorGraph/InflightGraphEditor.h"
#include "Graphs/InflightGraph.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"

#define LOCTEXT_NAMESPACE "InflightGraphBlueprintFactory"

UInflightGraphBlueprintFactory::UInflightGraphBlueprintFactory()
{
	bEditAfterNew = true;
	bCreateNew = true;
	SupportedClass = UInflightGraphBlueprint::StaticClass();
	ParentClass = UInflightGraph::StaticClass();
}

UObject* UInflightGraphBlueprintFactory::FactoryCreateNew(UClass* Class, UObject* InParent, const FName Name,
                                                          const EObjectFlags Flags, UObject* Context,
                                                          FFeedbackContext* Warn,
                                                          const FName CallingContext)
{
	// Make sure we are trying to factory a Inflight Graph Blueprint, then create and init one
	check(Class->IsChildOf(UInflightGraphBlueprint::StaticClass()));

	if (ParentClass == nullptr || !FKismetEditorUtilities::CanCreateBlueprintOfClass(ParentClass) ||
		!ParentClass->IsChildOf(UInflightGraph::StaticClass()))
	{
		FFormatNamedArguments Args;
		Args.Add(TEXT("ClassName"), ParentClass != nullptr ? FText::FromString(ParentClass->GetName()) : LOCTEXT("Null", "(null)"));
		FMessageDialog::Open( EAppMsgType::Ok, FText::Format( LOCTEXT("CannotCreateInflightGraphBlueprint",
					"Cannot create an Inflight Graph Blueprint based on the class '{ClassName}'."), Args));
		return nullptr;
	}

	UInflightGraphBlueprint* NewBP = CastChecked<UInflightGraphBlueprint>(
		FKismetEditorUtilities::CreateBlueprint(ParentClass, InParent, Name, BPTYPE_Normal,
			UInflightGraphBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), CallingContext));

	UInflightGraphBlueprint* RootInflightClass = UInflightGraphBlueprint::FindRootInflightGraphBlueprint(NewBP);
	if (RootInflightClass == nullptr)
	{
		UEdGraph* NewGraph = FBlueprintEditorUtils::CreateNewGraph(NewBP, "Inflight", UInflightGraphEditor::StaticClass(), UInflightEditorGraphSchema::StaticClass());

		const UEdGraphSchema* Schema = NewGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph(*NewGraph);

		NewBP->UbergraphPages.Add(NewGraph);
		NewBP->SetInflightGraph(NewGraph);

		FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(NewBP);

		NewBP->LastEditedDocuments.Add(NewGraph);
		NewGraph->bAllowDeletion = false;
		NewGraph->bAllowRenaming = false;
	}

	return NewBP;
}

UObject* UInflightGraphBlueprintFactory::FactoryCreateNew(UClass* Class, UObject* InParent, const FName Name,
                                                          const EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return FactoryCreateNew(Class, InParent, Name, Flags, Context, Warn, NAME_None);
}

#undef LOCTEXT_NAMESPACE