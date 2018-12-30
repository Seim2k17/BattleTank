// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Tank.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
    GENERATED_BODY()

public:
    ATank();

protected:
    void BeginPlay() override;

    UTankAimingComponent* TankAimingComp;

public:
    void Tick(float DeltaTime) override;

    void AimAt(FVector HitLocation);
};
