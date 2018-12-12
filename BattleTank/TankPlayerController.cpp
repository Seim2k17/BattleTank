// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include <DrawDebugHelpers.h>


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

	FVector HitLocation; // Out parameter


	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitLocation.ToString());
		// TODO tell controlled tank to aim at this point
	}

	

	
	
}

// Get world location if linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{

	// PseudoCode
	// Find the CrosshairPosition
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	// further: challenge lec 135: 4:56

	// "De-project" the screen position of the crosshair to a world direction
	// Line-trace along that look direction, and see what we hit (up to max range)

	FHitResult HitResult;
	FVector StartTrace = FVector::ZeroVector;
	if (auto Tank = GetControlledTank())
	{
		StartTrace = Tank->GetActorLocation();
	}
	// Position of the Middle of the screen, but with length X
	float LengthCast = 100.f;
	FVector EndTrace = FVector(960.f, 540.f, LengthCast);
	FCollisionQueryParams QueryParams;
	GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECollisionChannel::ECC_Visibility, QueryParams);

	DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, true, 3.f, 0, 2.f);

	if (HitResult.bBlockingHit)
	{
		HitLocation = HitResult.ImpactPoint;
		return true;
	}
	return false;
	
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


