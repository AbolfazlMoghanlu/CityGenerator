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

USTRUCT(BlueprintType)
struct FSidewalkModule
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTransform Transform;
};

UCLASS(BlueprintType)
class CITYMAKER_API USidewalkModuleDefinitionDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FSidewalkModule> SidewalkModules;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Bound;
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

UCLASS(BlueprintType)
class CITYMAKER_API ULineDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* BaseMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bChecker = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInterface* FillerMaterial;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Width = 35.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Length = 100.0f;
};

UCLASS(BlueprintType)
class CITYMAKER_API URoadObstacleDataAsset : public UDataAsset
{
	GENERATED_BODY()


public: 
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMesh* Module;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BoundSize = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float InstanceDistance = 150;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bMaintainLastInstance = true;
};