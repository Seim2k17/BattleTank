// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalEditorUtilityBase.h"
#include "MatExchangeBlutility.generated.h"

/**
 * 
 */

class UMaterialInterface;
class UStaticMeshActor;

USTRUCT(BlueprintType)
struct FMaterialArray
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MaterialExchange")
    TArray<UMaterialInterface*> Materials;
};

UCLASS()
class BATTLETANK_API UMatExchangeBlutility : public UGlobalEditorUtilityBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "MaterialExchange")
    void GatherMaterials();

    UFUNCTION(BlueprintCallable, Category = "MaterialExchange")
    void ReplaceMaterials();

    UPROPERTY()
    TArray<AActor*> SMActorArray;

    UPROPERTY(EditAnywhere, Category = "MaterialExchange")
    TArray<AActor*> SMLevelArray;

    UPROPERTY(EditAnywhere, Category = "MaterialExchange")
    TArray<AActor*> SMLibraryArray;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MaterialExchange")
    TMap<AActor*, FMaterialArray> SMActorMaterialMap;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MaterialExchange")
    TMap<AActor*, FMaterialArray> SMActorLibraryMap;

private:
    void GatherData(TArray<AActor*> SourceArray, TMap<AActor*, OUT FMaterialArray>& TargetMap);

    void FilterData(TArray<AActor*> SourceArray, FString LevelName,
                    OUT TArray<AActor*>& TargetArray);

    void Replace(FString SourceMat, FString TargetMat, UStaticMeshActor* TargetMesh);

    FString LevelName = TEXT("99_EmpyTestMap");

    FString LibraryName = TEXT("98_MaterialLibrary");

    FString SourceMat = TEXT("MI_Yellow");

    FString TargetMat = TEXT("MI_Red");
};
