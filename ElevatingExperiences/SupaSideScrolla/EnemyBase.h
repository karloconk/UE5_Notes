// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SupaSideScrollaCharacter.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class SUPASIDESCROLLA_API AEnemyBase : public ASupaSideScrollaCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UParticleSystem* DeathEffect;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* DeathSound;

public:
	void DestroyEnemy();
};
