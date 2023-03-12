// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RoadDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class CITYMAKER_API URoadDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* BaseMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* FillerMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInterface* CurveMaterial;
};
