// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    // move the barrel the right ammount this frame

    // given a max elevation speed, and the frame time
	auto Time = GetWorld()->GetTimeSeconds();
    UE_LOG(LogTemp, Warning, TEXT("%f : Elevate called with Speed: %f"),Time, RelativeSpeed);
}


