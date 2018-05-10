// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "EditorToolbar.h"
#include "EditorToolbarStyle.h"
#include "EditorToolbarCommands.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SBox.h"

#include "SlateIcon.h"
#include "Delegates/Delegate.h"
#include "Widgets/Images/SImage.h" 

#include "Framework/MultiBox/MultiBoxDefs.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "LevelEditor.h"
#include <SlateDelegates.h>
#include "Internationalization/Internationalization.h"
#include "EditorStyleSet.h"

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
		FEditorToolbarCommands::Get().PluginActionAlmang,
		FExecuteAction::CreateRaw(this, &FEditorToolbarModule::PluginButtonClicked),
		FCanExecuteAction());
		

	PluginCommands->MapAction(
		FEditorToolbarCommands::Get().PluginActionKang,
		FExecuteAction::CreateRaw(this, &FEditorToolbarModule::PluginButtonClicked2),
		FCanExecuteAction());

	PluginCommands->MapAction(FEditorToolbarCommands::Get().MenuItem_1,
		FExecuteAction::CreateStatic(&FEditorToolbarModule::MenuItem_1_Execute),
		FCanExecuteAction::CreateStatic(&FEditorToolbarModule::MenuItem_1_CanExecute) );


	//bool FEditorToolbarModule::MenuItem_1_CanExecute()
	//	void FEditorToolbarModule::MenuItem_1_Execute()

	PluginCommands->MapAction(
		FEditorToolbarCommands::Get().MenuItem_1,
		FExecuteAction::CreateRaw(this, &FEditorToolbarModule::MenuItem_1_Clicked),
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

void FEditorToolbarModule::PluginButtonClicked2()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
		LOCTEXT("PluginButtonDialogText2", "Add code to {0} in {1} to override this button's actions"),
		FText::FromString(TEXT("FEditorToolbarModule::PluginButtonClicked2()")),
		FText::FromString(TEXT("EditorToolbar.cpp"))
	);
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FEditorToolbarModule::MenuItem_1_Clicked()
{
	// Reset build options
	FText DialogText = FText::Format(
		LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
		FText::FromString(TEXT("FEditorToolbarModule::MenuItem_1_Clicked()")),
		FText::FromString(TEXT("EditorToolbar.cpp"))
	);
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FEditorToolbarModule::MenuItem_1_Execute()
{
	// Reset build options
	FText DialogText = FText::Format(
		LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
		FText::FromString(TEXT("FEditorToolbarModule::PluginButtonClicked()")),
		FText::FromString(TEXT("EditorToolbar.cpp"))
	);
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

bool FEditorToolbarModule::MenuItem_1_CanExecute()
{
	FText DialogText = FText::Format(
		LOCTEXT("MenuItem_1_CanExecute", "Add code to {0} in {1} to override this button's actions"),
		FText::FromString(TEXT("bool FEditorToolbarModule::MenuItem_1_CanExecute())")),
		FText::FromString(TEXT("FEditorToolbarModule.cpp"))
	);

	FMessageDialog::Open(EAppMsgType::Ok, DialogText);

	return true;
}

void FEditorToolbarModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FEditorToolbarCommands::Get().PluginActionAlmang);
}
 
void FEditorToolbarModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
//#define LOCTEXT_NAMESPACE "LevelToolBarBuildMenu"

	Builder.AddToolBarButton(FEditorToolbarCommands::Get().PluginActionAlmang);
	Builder.AddToolBarButton(FEditorToolbarCommands::Get().PluginActionKang);

	TSharedRef<FUICommandList> InCommandList = PluginCommands.ToSharedRef();
 
	Builder.AddComboButton(	FUIAction(), 
							FOnGetContent::CreateStatic(&FEditorToolbarModule::GenerateComboMenuContent, InCommandList),
							LOCTEXT("BuildCombo_Label", "Combo Options"), 
							LOCTEXT("BuildComboToolTip", "Combo options menu"), 
							FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Build"),
							true); 

}
 
TSharedRef< SWidget > FEditorToolbarModule::GenerateComboMenuContent(TSharedRef<FUICommandList> InCommandList)
{
	// Get all menu extenders for this context menu from the level editor module
	FLevelEditorModule& LevelEditorModule = FModuleManager::GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	TArray<FLevelEditorModule::FLevelEditorMenuExtender> MenuExtenderDelegates = LevelEditorModule.GetAllLevelEditorToolbarBuildMenuExtenders();

	TArray<TSharedPtr<FExtender>> Extenders;
	for (int32 i = 0; i < MenuExtenderDelegates.Num(); ++i)
	{
		if (MenuExtenderDelegates[i].IsBound())
		{
			Extenders.Add(MenuExtenderDelegates[i].Execute(InCommandList));
		}
	}
	TSharedPtr<FExtender> MenuExtender = FExtender::Combine(Extenders);

	const bool bShouldCloseWindowAfterMenuSelection = true;
	FMenuBuilder MenuBuilder(bShouldCloseWindowAfterMenuSelection, InCommandList, MenuExtender);

	//MenuBuilder
	MenuBuilder.BeginSection("FEditorToolbarModule1", LOCTEXT("FEditorToolbarModule2", "Kang MenuItems"));
	{
		MenuBuilder.AddMenuEntry(FEditorToolbarCommands::Get().MenuItem_1, NAME_None, LOCTEXT("MenuItem", "MenuItem_1"));
	}
	MenuBuilder.EndSection();


 


	return MenuBuilder.MakeWidget();
}



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FEditorToolbarModule, EditorToolbar)