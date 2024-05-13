#include "Target.h"
#include "Components/SphereComponent.h"
#include "ExampleProjectile.h"

ATarget::ATarget()
{
	_TargetCollision = CreateDefaultSubobject<USphereComponent>(TEXT("TargetCollision"));
	_TargetCollision->SetupAttachment(RootComponent);
	_TargetCollision->OnComponentBeginOverlap.AddDynamic(this, &ATarget::OnTargetCollisionBeginOverlap);
}

void ATarget::OnTargetCollisionBeginOverlap(AActor* OtherActor, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ExampleProjectile* otherProj = Cast<AExampleProjectile>(OtherActor))
	{
		_TimesHit++;

		if (_TimesHit == 10)
		{
			TenHitVisuals();
		}
	}
}

Void ATarget::TenHitVisuals()
{
	return Void();
}
