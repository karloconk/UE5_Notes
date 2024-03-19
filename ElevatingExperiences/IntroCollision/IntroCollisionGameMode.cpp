// Copyright Epic Games, Inc. All Rights Reserved.

#include "IntroCollisionGameMode.h"
#include "IntroCollisionCharacter.h"
#include "UObject/ConstructorHelpers.h"

AIntroCollisionGameMode::AIntroCollisionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
