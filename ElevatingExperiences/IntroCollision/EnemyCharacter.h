// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class INTROCOLLISION_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LookAt", meta = (AllowPrivateAccess = "true"))
	class ULookAtActorComponent* LookAtActorComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dodgeball", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ADodgeballProjectile> DodgeballClass;

private:
	bool bCanSeePLayer { false };
	bool bPreviousCanSeePlayer { false };

protected:
	FTimerHandle ThrowTimerHandle;
	float ThrowingInterval { 2.f };
	float ThrowingDelay { 0.5f };

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void ThrowDodgeball();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
