// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
    GENERATED_BODY()

public:
    ATank();

    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetBarrelReference(UTankBarrel* BarrelToSet);

    void Tick(float DeltaTime) override;

    void AimAt(FVector HitLocation);

    UPROPERTY(EditAnywhere, Category = Firing)
    float LaunchSpeed = 10000.0f; // Sensible starting value of 1000 m/s

protected:
    void BeginPlay() override;

    UTankAimingComponent* TankAimingComp;
};
