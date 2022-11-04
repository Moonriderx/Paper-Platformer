// Copyright Epic Games, Inc. All Rights Reserved.

#include "PaperZGameMode.h"
#include "PaperZCharacter.h"
#include "UObject/ConstructorHelpers.h"

APaperZGameMode::APaperZGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
