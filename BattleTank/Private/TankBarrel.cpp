// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSeconds)
{
    // move the barrel the right ammount this frame

    // given a max elevation speed, and the frame time

    UE_LOG(LogTemp, Warning, TEXT("Elevate called"));
}

void UTankBarrel::SetBarrelReference(UStaticMeshComponent* BarrelMeshToSet)
{
    BarrelMesh = BarrelMeshToSet;
}
