// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EditorToolbarCommands.h"

#define LOCTEXT_NAMESPACE "FEditorToolbarModule"

void FEditorToolbarCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "EditorToolbar", "Execute EditorToolbar action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
