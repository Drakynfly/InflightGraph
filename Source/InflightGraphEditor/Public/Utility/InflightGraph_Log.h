// Copyright Guy (Drakynfly) Lundvall. All Rights Reserved.

#pragma once

DECLARE_LOG_CATEGORY_EXTERN(LogInflightGraphEditor, Verbose, All);
#define INFLIGHTGRAPH_LOG(Message,...) UE_LOG(LogInflightGraphEditor, Log, TEXT(Message), ##__VA_ARGS__)
#define INFLIGHTGRAPH_DISPLAY(Message,...) UE_LOG(LogInflightGraphEditor, Display, TEXT(Message), ##__VA_ARGS__)
#define INFLIGHTGRAPH_WARNING(Message,...) UE_LOG(LogInflightGraphEditor, Warning, TEXT(Message), ##__VA_ARGS__)
#define INFLIGHTGRAPH_ERROR(Message,...) UE_LOG(LogInflightGraphEditor, Error, TEXT(Message), ##__VA_ARGS__)