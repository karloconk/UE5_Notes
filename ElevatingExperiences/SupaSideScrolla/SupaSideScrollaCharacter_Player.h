// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SupaSideScrollaCharacter.h"
#include "SupaSideScrollaCharacter_Player.generated.h"

/**
 * 
 */
UCLASS()
class SUPASIDESCROLLA_API ASupaSideScrollaCharacter_Player : public ASupaSideScrollaCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class APlayerProyectile> PlayerProjectile;

protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputMappingContext* IC_Character;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Sprint;
	UPROPERTY(EditAnywhere, Category = "Input")
	class UInputAction* IA_Throw;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* ThrowMontage;

public:
	UFUNCTION(BlueprintPure)
	int32 GetCurrentNumberofCollectables() { return NumberofCollectables; };

private:
	bool bIsSprinting;
	int32 NumberofCollectables;
	FTimerHandle PowerupHandle;
	bool bHasPowerUpActive;
	
protected:
	ASupaSideScrollaCharacter_Player();

	virtual void SetupPlayerInputComponent(class UInputComponent*) override;

	void Sprint();
	void StopSprinting();
	void ThrowProjectile();
	void EndPowerup();

public:
	void SpawnProjectile();
	void IncrementNumberofCollectables(int32  Value);
	void IncreaseMovementPowerup();

};
