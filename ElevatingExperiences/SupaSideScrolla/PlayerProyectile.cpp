// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerProyectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyBase.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerProyectile::APlayerProyectile()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComponent->InitSphereRadius(15.f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("BlockAll");
	CollisionComponent->OnComponentHit.AddDynamic(this, &APlayerProyectile::OnHit);
	RootComponent = CollisionComponent;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComponent;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->InitialSpeed = 800.0f;
	ProjectileMovement->MaxSpeed = 800.0f;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponent->AttachToComponent(	RootComponent, 
		FAttachmentTransformRules::KeepWorldTransform);
	InitialLifeSpan = 3.f;

	ProjectileMovementSound = CreateDefaultSubobject<UAudioComponent>(TEXT("ProjectileMovementSound"));
	ProjectileMovementSound->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	ProjectileEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileEffect"));
	ProjectileEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
}

void APlayerProyectile::ExplodeProjectile()
{
	if (UWorld* World = GetWorld())
	{
		if (DestroyEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				World,
				DestroyEffect,
				GetActorTransform());
		}
		if (DestroySound)
		{
			UGameplayStatics::SpawnSoundAtLocation(
				World,
				DestroySound,
				GetActorLocation());
		}
	}
	Destroy();
}

void APlayerProyectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (AEnemyBase* Enemy{ Cast<AEnemyBase>(OtherActor) })
	{
		Enemy->DestroyEnemy();
	}
	ExplodeProjectile();
}