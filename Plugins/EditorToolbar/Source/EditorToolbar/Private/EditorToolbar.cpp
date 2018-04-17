// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EditorToolbar.h"
#include "EditorToolbarStyle.h"
#include "EditorToolbarCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "LevelEditor.h"

static const FName EditorToolbarTabName("EditorToolbar");

#define LOCTEXT_NAMESPACE "FEditorToolbarModule"

void FEditorToolbarModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FEditorToolbarStyle::Initialize();
	FEditorToolbarStyle::ReloadTextures();

	FEditorToolbarCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FEditorToolbarCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FEditorToolbarModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FEditorToolbarModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FEditorToolbarModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
}

void FEditorToolbarModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FEditorToolbarStyle::Shutdown();

	FEditorToolbarCommands::Unregister();
}

void FEditorToolbarModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FEditorToolbarModule::PluginButtonClicked()")),
							FText::FromString(TEXT("EditorToolbar.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FEditorToolbarModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FEditorToolbarCommands::Get().PluginAction);
}

void FEditorToolbarModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FEditorToolbarCommands::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorToolbarModule, EditorToolbar)