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

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* BufferMesh;
};

UCLASS()
class CITYMAKER_API USidewalkDataAsset : public UDataAsset
{
	GENERATED_BODY()


public:

	// module 0 is also filler 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UStaticMesh*> SidewalkModules;
};


UCLASS()
class CITYMAKER_API UPedestrianLineDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* BaseMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float LinesDistance;
};