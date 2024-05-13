#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

UCLASS(Abstract)
class EXAMPLE_API ATarget : publicAActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* _TargetCollision;

	int _TimesHit{0};

public:
	ATarget();

	UFUNCTION()
	void OnTargetCollisionBeginOverlap(AActor* OtherActor,
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	Void TenHitVisuals();

};