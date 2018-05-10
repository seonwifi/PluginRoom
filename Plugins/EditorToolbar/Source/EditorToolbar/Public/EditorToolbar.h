// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SWidget.h"
#include "Framework/Commands/UICommandList.h"
#include "ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FEditorToolbarModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	
	void PluginButtonClicked2();

	static bool MenuItem_1_CanExecute();
	static void MenuItem_1_Execute();
	void MenuItem_1_Clicked();
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

public:
	static TSharedRef< SWidget > GenerateComboMenuContent(TSharedRef<FUICommandList> InCommandList); 
private:
	TSharedPtr<class FUICommandList> PluginCommands;

};