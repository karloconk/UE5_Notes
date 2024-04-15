// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerProyectile.generated.h"

UCLASS()
class SUPASIDESCROLLA_API APlayerProyectile : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	class USphereComponent* CollisionComponent;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Sound")
	class UAudioComponent* ProjectileMovementSound;

	UPROPERTY(VisibleDefaultsOnly, Category = "Projectile")
	class UParticleSystemComponent* ProjectileEffect;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* DestroySound;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	class UParticleSystem* DestroyEffect;

public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);
	
public:	
	// Sets default values for this actor's properties
	APlayerProyectile();

	void ExplodeProjectile();

};
