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
		Transform(FTransform::Identity)
		{};

	UPROPERTY(BlueprintReadWrite)
	FTransform Transform;

	UPROPERTY(BlueprintReadWrite)
	int32 BatchIndex;
};


USTRUCT(BlueprintType)
struct CITYMAKER_API FCityPointClouds
{
	GENERATED_BODY()

public:
	void Clear();

	UPROPERTY(BlueprintReadWrite)
	TArray<FRoadPointCloud> RoadPoints;
};