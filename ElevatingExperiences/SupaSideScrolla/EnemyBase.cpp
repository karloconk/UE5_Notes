// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void AEnemyBase::DestroyEnemy()
{
	if (UWorld* World = GetWorld())
	{
		if (DeathEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				World, 
				DeathEffect, 
				GetActorTransform());
		}
		if (DeathSound)
		{
			UGameplayStatics::SpawnSoundAtLocation(
				World, 
				DeathSound, 
				GetActorLocation());
		}
	}

	Destroy();
}
