// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()
	
public:	
	
	ATank();

protected:
	
	void BeginPlay() override;

public:	
	
	void Tick(float DeltaTime) override;

	
	
};