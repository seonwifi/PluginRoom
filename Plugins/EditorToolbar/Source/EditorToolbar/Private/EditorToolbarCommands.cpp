// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EditorToolbarCommands.h"

#define LOCTEXT_NAMESPACE "FEditorToolbarModule"

void FEditorToolbarCommands::RegisterCommands()
{
	UI_COMMAND(PluginActionAlmang, "Almang", "Execute EditorToolbar action", EUserInterfaceActionType::Button, FInputGesture());

	UI_COMMAND(PluginActionKang, "Kang", "Execute EditorToolbar action2", EUserInterfaceActionType::Button, FInputGesture());

	UI_COMMAND(MenuItem_1, "MenuItem_1", "Execute MenuItem_1", EUserInterfaceActionType::Button, FInputGesture());
	
}

#undef LOCTEXT_NAMESPACE
