// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:

	ATankPlayerController();

	ATank* GetControlledTank() const;
	
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

private:
	// start the tank moving the barrel so that the shot would hit what the crosshair would hit
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;
	
};
