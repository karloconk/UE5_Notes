// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableActor_Base.generated.h"

UCLASS()
class SUPASIDESCROLLA_API APickableActor_Base : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "PickableItem")
	class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "PickableItem")
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "PickableItem")
	class URotatingMovementComponent* RotationComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USoundBase* PickupSound;

private:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

public:	
	// Sets default values for this actor's properties
	APickableActor_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PlayerPickedUp(class ASupaSideScrollaCharacter_Player* PLayer);
	
};
