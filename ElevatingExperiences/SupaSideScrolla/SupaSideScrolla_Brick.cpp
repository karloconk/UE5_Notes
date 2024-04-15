// Fill out your copyright notice in the Description page of Project Settings.


#include "SupaSideScrolla_Brick.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "SupaSideScrollaCharacter_Player.h"

// Sets default values
ASupaSideScrolla_Brick::ASupaSideScrolla_Brick()
{
	PrimaryActorTick.bCanEverTick = false;

	BrickMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BrickMesh"));
	BrickMesh->SetCollisionProfileName("BlockAll");
	RootComponent = BrickMesh;

	BrickCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BrickCollision"));
	BrickCollision->SetCollisionProfileName("BlockAll");
	BrickCollision->AttachToComponent(RootComponent,	FAttachmentTransformRules::KeepWorldTransform);
	BrickCollision->OnComponentHit.AddDynamic(this, &ASupaSideScrolla_Brick::OnHit);
}

void ASupaSideScrolla_Brick::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ASupaSideScrollaCharacter_Player* Player = Cast<ASupaSideScrollaCharacter_Player>(OtherActor);
	if (Player && bHasCollectable)
	{
		AddCollectable(Player);
		PlayHitSound();
		PlayHitExplosion();
	}
	Destroy();
}


// Called when the game starts or when spawned
void ASupaSideScrolla_Brick::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASupaSideScrolla_Brick::AddCollectable(ASupaSideScrollaCharacter_Player* Player)
{
	Player->IncrementNumberofCollectables(CollectableValue);
}

void ASupaSideScrolla_Brick::PlayHitSound()
{
	UWorld* World = GetWorld();
	if (World && HitSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(
			World,
			HitSound,
			GetActorLocation());
	}
}

void ASupaSideScrolla_Brick::PlayHitExplosion()
{
	UWorld* World = GetWorld();
	if (World && Explosion)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			World,
			Explosion,
			GetActorTransform());
	}
}


