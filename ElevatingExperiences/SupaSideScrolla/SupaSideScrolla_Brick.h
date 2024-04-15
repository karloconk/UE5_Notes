// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SupaSideScrolla_Brick.generated.h"

UCLASS()
class SUPASIDESCROLLA_API ASupaSideScrolla_Brick : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Brick")
	class UStaticMeshComponent* BrickMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Brick")
	class UBoxComponent* BrickCollision;

	UPROPERTY(EditAnywhere)
	bool bHasCollectable;

	UPROPERTY(EditAnywhere)
	int32 CollectableValue{ 1 };

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Brick")
	class USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Brick")
	class UParticleSystem* Explosion;

private:
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp, 
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);
	
public:	
	// Sets default values for this actor's properties
	ASupaSideScrolla_Brick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void AddCollectable(class ASupaSideScrollaCharacter_Player* Player);
	void PlayHitSound();
	void PlayHitExplosion();

};
