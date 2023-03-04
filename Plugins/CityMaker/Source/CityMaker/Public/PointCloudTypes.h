// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PointCloudTypes.generated.h"

USTRUCT(BlueprintType)
struct CITYMAKER_API FRoadPointCloud
{
	GENERATED_BODY()

public:
	FRoadPointCloud() :
		Transform(FTransform::Identity),
		RoadType(0),
		RoadVar(0)
		{};

	UPROPERTY(BlueprintReadWrite)
	FTransform Transform;

	UPROPERTY(BlueprintReadWrite)
	int RoadType;

	UPROPERTY(BlueprintReadWrite)
	int RoadVar;
};

USTRUCT(BlueprintType)
struct CITYMAKER_API FRoadsData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FRoadPointCloud> Points;

	UPROPERTY(BlueprintReadWrite)
	int BatchCount = -1;
};

USTRUCT(BlueprintType)
struct CITYMAKER_API FCityData
{
	GENERATED_BODY()

public:
	void Clear();

	UPROPERTY(BlueprintReadWrite)
	FRoadsData RoadData;
};