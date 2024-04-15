// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_Collectable.h"
#include "SupaSideScrollaCharacter_Player.h"

void APickableActor_Collectable::BeginPlay()
{
	Super::BeginPlay();
}

void APickableActor_Collectable::PlayerPickedUp(ASupaSideScrollaCharacter_Player* PLayer)
{
	PLayer->IncrementNumberofCollectables(CollectableValue);
	Super::PlayerPickedUp(PLayer);
}
