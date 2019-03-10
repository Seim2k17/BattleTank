// Fill out your copyright notice in the Description page of Project Settings.

#include "MatExchangeBlutility.h"
#include <Engine/StaticMeshActor.h>
#include <Kismet/GameplayStatics.h>
#include <Materials/MaterialInstance.h>

void UMatExchangeBlutility::GatherMaterials()
{
    UGameplayStatics::GetAllActorsOfClass(this, AStaticMeshActor::StaticClass(), SMActorArray);

    FilterData(SMActorArray, LevelName, SMLevelArray);

    FilterData(SMActorArray, LibraryName, SMLibraryArray);

    GatherData(SMLibraryArray, SMActorLibraryMap);

    GatherData(SMLevelArray, SMActorMaterialMap);
}

void UMatExchangeBlutility::ReplaceMaterials()
{
    Replace(SourceMat, TargetMat);
}

void UMatExchangeBlutility::GatherData(TArray<AActor*> SourceArray,
                                       TMap<AActor*, OUT FMaterialArray>& TargetMap)
{
    // from which Source we make our MaterialMap ?
    for (auto* Mesh : SourceArray)
    {
        TArray<UActorComponent*> MeshComps =
            Mesh->GetComponentsByClass(UStaticMeshComponent::StaticClass());

        for (auto* MeshComp : MeshComps)
        {
            if (auto* Component = Cast<UStaticMeshComponent>(MeshComp))
            {
                UE_LOG(LogTemp, Log, TEXT("SMComp from %s: %s"), *Mesh->GetName(),
                       *MeshComp->GetName());

                TArray<UMaterialInterface*> MeshMaterials = Component->GetMaterials();
                FMaterialArray MatArray;
                MatArray.Materials = MeshMaterials;

                TargetMap.Add(Mesh, MatArray);
            }
        }
    }
}

void UMatExchangeBlutility::FilterData(TArray<AActor*> SourceArray, FString LevelName,
                                       OUT TArray<AActor*>& TargetArray)
{
    TargetArray = SourceArray.FilterByPredicate(
        [LevelName](AActor* Mesh) { return (Mesh->GetFullName().Contains(LevelName)); });
}

void UMatExchangeBlutility::Replace(FString SourceMat, FString TargetMat)
{
    for (auto Actor : SMActorMaterialMap)
    {
        for (auto Material : Actor.Value.Materials)
        {
            UE_LOG(LogTemp, Warning, TEXT("Actor: %s, Materials: %s"), *Actor.Key->GetName(),
                   *Material->GetName());
            if (Material->GetName().Contains(SourceMat))
            {
				ReplaceMaterial(Actor.Key, TargetMat);
            }
        }
    }
}

void UMatExchangeBlutility::ReplaceMaterial(AActor* Actor, FString TargetMat)
{
	TArray<UActorComponent*> MeshComps =
		Actor->GetComponentsByClass(UStaticMeshComponent::StaticClass());

	for (auto* MeshComp : MeshComps)
	{
		if (auto* Component = Cast<UStaticMeshComponent>(MeshComp))
		{
			if (UMaterialInterface* TargetMaterial = FindMaterialInLibrary(TargetMat))
			{
				Component->SetMaterial(0, TargetMaterial);
			}
			
		}
	}
}

UMaterialInterface* UMatExchangeBlutility::FindMaterialInLibrary(FString TargetMat)
{

	UMaterialInterface* FoundMaterial = nullptr;

	for (auto Actor : SMActorLibraryMap)
	{
		for (auto Material : Actor.Value.Materials)
		{
			if (Material->GetName().Contains(TargetMat))
			{
				FoundMaterial = Material;
			}
		}
	}

	return FoundMaterial;
}
