// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include <DrawDebugHelpers.h>

ATankPlayerController::ATankPlayerController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
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
        // TODO tell controlled tank to aim at this point
        GetControlledTank()->AimAt(HitLocation);
    }
}

// Get world location if linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    // PseudoCode
    // Find the CrosshairPosition in pixel coordinates
    int32 ViewPortSizeX, ViewPortSizeY;
    GetViewportSize(ViewPortSizeX, ViewPortSizeY);
    // further: challenge lec 135: 4:56

    FVector2D ScreenLocation =
        FVector2D(CrossHairXLocation * ViewPortSizeX, CrossHairYLocation * ViewPortSizeY);

    // UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

    // "De-project" the screen position of the crosshair to a world direction

    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        return GetLookVectorHitLocation(LookDirection, HitLocation);
        // UE_LOG(LogTemp, Warning, TEXT("WorldDirection: %s"), *LookDirection.ToString());
    }

    return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection,
                                                     FVector& HitLocation) const
{
    FHitResult HitResult;
    FVector StartTrace = PlayerCameraManager->GetCameraLocation();

    // Position of the Middle of the screen, but with length X
    FVector EndTrace = StartTrace + (LineTraceRange * LookDirection);
    FCollisionQueryParams QueryParams;
    if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace,
                                             ECollisionChannel::ECC_Visibility, QueryParams))
    {
        DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, true, 3.f, 0, 2.f);

        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector::ZeroVector;
    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    // to be discarded
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation,
                                          LookDirection);
}

ATank* ATankPlayerController::GetControlledTank() const
{
    auto Tank = Cast<ATank>(GetPawn());

    if (Tank)
    {
        // UE_LOG(LogTemp, Warning, TEXT("The Controlled Tank is: %s"), *GetPawn()->GetName());
    }
    else
    {
        // UE_LOG(LogTemp, Warning, TEXT("No posseded Tank found."));
    }

    return Tank;
}
