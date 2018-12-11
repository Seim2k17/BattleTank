// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATankPlayerController::ATankPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();


	auto Tank = GetControlledTank();
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())
	{
		return;
	}

	// Get world location if linetrace through crosshair
	// if it hits landscape
		// tell controlled tank to aim at this point
}

ATank* ATankPlayerController::GetControlledTank() const
{
	auto Tank = Cast<ATank>(GetPawn());

	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("The Controlled Tank is: %s"), *GetPawn()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No posseded Tank found."));
	}

	return Tank;
}


