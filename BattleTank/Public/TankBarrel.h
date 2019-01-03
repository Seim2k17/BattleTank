// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS()
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
    GENERATED_BODY()

public:
    void Elevate(float DegreesPerSeconds);

    void SetBarrelReference(UStaticMeshComponent* BarrelMeshToSet);

private:
    UStaticMeshComponent* BarrelMesh = nullptr;
};
