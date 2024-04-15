// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_ProjectileNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "SupaSideScrolla/SupaSideScrollaCharacter_Player.h"

void UAnim_ProjectileNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	if (ASupaSideScrollaCharacter_Player* Player = Cast<ASupaSideScrollaCharacter_Player>(MeshComp->GetOwner()))
	{
		Player->SpawnProjectile();
	}

}
