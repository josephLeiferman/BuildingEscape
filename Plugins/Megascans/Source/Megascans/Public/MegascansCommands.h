// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "MegascansStyle.h"

class FMegascansCommands : public TCommands<FMegascansCommands>
{
public:

	FMegascansCommands()
		: TCommands<FMegascansCommands>(TEXT("Megascans"), NSLOCTEXT("Contexts", "Megascans", "Megascans Plugin"), NAME_None, FMegascansStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
