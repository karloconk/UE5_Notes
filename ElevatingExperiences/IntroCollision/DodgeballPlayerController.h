// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DodgeballPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class INTROCOLLISION_API ADodgeballPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class URestartWidget> BP_RestartWidget;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDWidget> BP_HUDWidget;
	
private:
	UPROPERTY() // made this way to avoid being destroyed by the garbage collector
	class URestartWidget* RestartWidget;
	UPROPERTY() 
	class UHUDWidget* HUDWidget;

public: 
	void ShowRestartWidget();
	void HideRestartWidget();

	void UpdateHealthPercent(float HealthPercent);

protected:
	virtual void BeginPlay() override;

};
