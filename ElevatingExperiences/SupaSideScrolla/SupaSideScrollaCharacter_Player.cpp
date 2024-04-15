// Fill out your copyright notice in the Description page of Project Settings.


#include "SupaSideScrollaCharacter_Player.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Animation/AnimInstance.h"
#include "Engine/World.h"
#include "Components/SphereComponent.h"
#include "PlayerProyectile.h"
#include "TimerManager.h"

ASupaSideScrollaCharacter_Player::ASupaSideScrollaCharacter_Player()
{
	bIsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}

void ASupaSideScrollaCharacter_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedPlayerInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		APlayerController* PlayerController =
			Cast<APlayerController>(GetController());

		if (UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			EnhancedSubsystem->AddMappingContext(IC_Character, 1);
		}

		//Bind pressed action Sprint to your Sprint function
		EnhancedPlayerInput->BindAction(
			IA_Sprint,
			ETriggerEvent::Triggered, 
			this, 
			&ASupaSideScrollaCharacter_Player::Sprint);
		EnhancedPlayerInput->BindAction(
			IA_Sprint,
			ETriggerEvent::Completed, 
			this, 
			&ASupaSideScrollaCharacter_Player::StopSprinting);
		EnhancedPlayerInput->BindAction(
			IA_Throw,
			ETriggerEvent::Triggered,
			this,
			&ASupaSideScrollaCharacter_Player::ThrowProjectile);
	}
}

void ASupaSideScrollaCharacter_Player::Sprint()
{
	if (!bIsSprinting)
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = bHasPowerUpActive ? 900.f : 500.f;
	}
}

void ASupaSideScrollaCharacter_Player::StopSprinting()
{
	if (bIsSprinting)
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = bHasPowerUpActive ? 500.f : 300.0f;
	}

}

void ASupaSideScrollaCharacter_Player::ThrowProjectile()
{
	if (ThrowMontage)
	{
		const bool bIsMontagePlaying = GetMesh()->GetAnimInstance()->Montage_IsPlaying(ThrowMontage);
		if (!bIsMontagePlaying)
		{
			GetMesh()->GetAnimInstance()->Montage_Play(ThrowMontage,	1.0f);
		}
	}
}

void ASupaSideScrollaCharacter_Player::EndPowerup()
{
	bHasPowerUpActive = false;

	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(PowerupHandle);
	}
}

void ASupaSideScrollaCharacter_Player::SpawnProjectile()
{
	if (PlayerProjectile)
	{
		if (UWorld* World = GetWorld())
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;

			const FVector SpawnLocation{ this->GetMesh()->GetSocketLocation(FName("ProjectileSocket")) };
			const FRotator Rotation{ GetActorForwardVector().Rotation() };

			APlayerProyectile* Projectile = World->SpawnActor<APlayerProyectile>(
			PlayerProjectile,
			SpawnLocation,
			Rotation, 
			SpawnParams);

		}
	}
}

void ASupaSideScrollaCharacter_Player::IncrementNumberofCollectables(int32 Value)
{
	if (Value == 0)
	{
		return;
	}
	NumberofCollectables += Value;
	UE_LOG(LogTemp, Warning, TEXT("Number of Coins: %d"), NumberofCollectables);
}

void ASupaSideScrollaCharacter_Player::IncreaseMovementPowerup()
{
	bHasPowerUpActive = true;

	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->JumpZVelocity = 1500.f;
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(
			PowerupHandle,
			this,
			&ASupaSideScrollaCharacter_Player::EndPowerup,
			8.0f,
			false);
	}
}
