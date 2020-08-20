// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "MegascansCommands.h"

#define LOCTEXT_NAMESPACE "FMegascansModule"

void FMegascansCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "Megascans", "Execute Megascans action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
