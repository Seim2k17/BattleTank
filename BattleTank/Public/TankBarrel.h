// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "TankBarrel.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hideCategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
    GENERATED_BODY()

public:
    void Elevate(float DegreesPerSeconds);

    void SetBarrelReference(UStaticMeshComponent* BarrelMeshToSet);

private:
    UStaticMeshComponent* BarrelMesh = nullptr;

    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxDegreesPerSeconds = 20.0f;

    UPROPERTY(EditAnywhere, Category = Setup)
    float MaxElevationDegrees = 40.0f;

    UPROPERTY(EditAnywhere, Category = Setup)
    float MinElevationDegrees = 0.0f;
};
