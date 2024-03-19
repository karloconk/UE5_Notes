// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeballFunctionLibrary.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

bool UDodgeballFunctionLibrary::CanSeeActor(const UWorld* World, FVector Location, const AActor* TargetActor, TArray<const AActor*> IgnoreActors)
{
	if (!TargetActor) { return false; }

	FHitResult Hit;
	FVector Start{ Location };
	FVector End = TargetActor->GetActorLocation();

	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(IgnoreActors);
	QueryParams.AddIgnoredActor(TargetActor); // Adding cos this is not the hit, this is to see if there is something between them

	World->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);
	DrawDebugLine(World, Start, End, FColor::Green);
	return !Hit.bBlockingHit;
}
