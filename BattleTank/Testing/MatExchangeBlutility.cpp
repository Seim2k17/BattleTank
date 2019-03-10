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

void UMatExchangeBlutility::Replace(FString SourceMat, FString TargetMat,
                                    UStaticMeshActor* TargetMesh)
{


}
