// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "DodgeballProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "LookAtActorComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LookAtActorComponent = CreateDefaultSubobject<ULookAtActorComponent>(TEXT("Look At Actor Component"));
	LookAtActorComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	LookAtActorComponent->SetTarget(PlayerCharacter);
}

void AEnemyCharacter::ThrowDodgeball()
{
	if (!DodgeballClass) { return; }

	FVector ForwardVector { GetActorForwardVector() };
	float SpawnDistance { 40.f };
	FVector SpawnLocation { GetActorLocation() + ForwardVector * SpawnDistance };
	
	FTransform SpawnTransform{ FTransform(GetActorRotation(), SpawnLocation) };
	ADodgeballProjectile* Projectile = { GetWorld()->SpawnActorDeferred<ADodgeballProjectile>(DodgeballClass, SpawnTransform) };
	Projectile->GetProjectileMovementComponent()->InitialSpeed = 2200;
	Projectile->FinishSpawning(SpawnTransform);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bCanSeePLayer = LookAtActorComponent->CanSeeTarget();

	if (bCanSeePLayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePLayer)
		{
			GetWorldTimerManager().SetTimer(
				ThrowTimerHandle, 
				this, 
				&AEnemyCharacter::ThrowDodgeball, 
				ThrowingInterval, 
				true, 
				ThrowingDelay);
		}
		else
		{
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
		}
	}

	bPreviousCanSeePlayer = bCanSeePLayer;
}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

