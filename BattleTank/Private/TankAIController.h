// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class ATankAIController : public AAIController
{
    GENERATED_BODY()

public:
    ATankAIController();
    void Tick(float DeltaTime) override;

protected:
    void BeginPlay() override;

    ATank* GetControlledTank() const;

    ATank* GetPlayerTank() const;
};
