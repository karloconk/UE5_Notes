// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DodgeballProjectile.generated.h"

UCLASS()
class INTROCOLLISION_API ADodgeballProjectile : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dodgeball", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dodgeball", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;


	UPROPERTY(EditAnywhere, Category = "Particles")
	class UParticleSystem* HitParticles;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* BounceSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* DamageSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundAttenuation* BounceSoundAttenuation;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage{ 34.f };

public:	
	// Sets default values for this actor's properties
	ADodgeballProjectile();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovementComponent() const
	{
		return ProjectileMovement;
	}

};
