// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"




void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto Tank = GetControlledTank();
	
	auto PlayerTank = GetPlayerTank();
}

ATank* ATankAIController::GetControlledTank() const
{
	auto Tank = Cast<ATank>(GetPawn());

	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController: The Controlled Tank is: %s"), *GetPawn()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No posseded Tank found."));
	}

	return Tank;
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if(PlayerTank)
	{
		UE_LOG(LogTemp, Log, TEXT("The Player is: %s"), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Player found"));
	}

	return PlayerTank;
}

