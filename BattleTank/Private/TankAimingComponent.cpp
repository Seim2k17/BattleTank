// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Kismet/GameplayStatics.h"

UTankAimingComponent::UTankAimingComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
    // protecting the Barrel reference
    if (!Barrel)
    {
        return;
    }

    FVector OutLaunchVelocity;
    FVector StartLocation = Barrel->GetSocketLocation(FName("ProjectileStart"));

    bool bHaveAimSolution =
        UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation,
                                                    HitLocation, LaunchSpeed, false, 0.f, 0.f,
                                                    ESuggestProjVelocityTraceOption::TraceFullPath);

    // Calculate the OutLaunchVelocity and only if success, succeed
    if (bHaveAimSolution)
    {
        // turns the OutLaunchVelocity into a normalized DirectionVector
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        auto TankName = GetOwner()->GetName();
        //         UE_LOG(LogTemp, Warning, TEXT("%s Aiming at %s "), *TankName, *AimDirection.ToString(),
        //                *OutLaunchVelocity.ToString());
        MoveBarrelTowards(AimDirection);
    }
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    // Pseudocode
    // work-out difference between current barrel rotation and aim direction
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;

    Barrel->Elevate(5); // TODO remove magic number
}
