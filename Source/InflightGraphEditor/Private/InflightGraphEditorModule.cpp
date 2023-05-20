// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#include "InflightGraphEditorModule.h"

DEFINE_LOG_CATEGORY(LogInflightGraphEditor)

#define LOCTEXT_NAMESPACE "InflightGraphEditorModule"

void FInflightGraphEditor::StartupModule()
{
}


void FInflightGraphEditor::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FInflightGraphEditor, InflightGraphEditor)