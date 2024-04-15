// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor_Base.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "SupaSideScrollaCharacter_Player.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickableActor_Base::APickableActor_Base()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(30.f);
	CollisionComponent->BodyInstance.SetCollisionProfileName("OverlapAllDynamic");	
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &APickableActor_Base::BeginOverlap);
	RootComponent = CollisionComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->AttachToComponent(RootComponent, 	FAttachmentTransformRules::KeepWorldTransform);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RotationComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotationComponent"));
}

// Called when the game starts or when spawned
void APickableActor_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickableActor_Base::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ASupaSideScrollaCharacter_Player* Player = Cast<ASupaSideScrollaCharacter_Player>(OtherActor))
	{
		PlayerPickedUp(Player);
	}
}

void APickableActor_Base::PlayerPickedUp(ASupaSideScrollaCharacter_Player* PLayer)
{
	if (const UWorld* World = GetWorld())
	{
		if (PickupSound)
		{
			UGameplayStatics::SpawnSoundAtLocation(
				World,
				PickupSound,
				GetActorLocation());
		}
	}
	Destroy();
}

