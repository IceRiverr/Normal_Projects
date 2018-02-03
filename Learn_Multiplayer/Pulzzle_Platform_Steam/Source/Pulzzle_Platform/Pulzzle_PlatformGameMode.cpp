// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Pulzzle_PlatformGameMode.h"
#include "Pulzzle_PlatformCharacter.h"
#include "UObject/ConstructorHelpers.h"

APulzzle_PlatformGameMode::APulzzle_PlatformGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
