// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PointCloudTypes.generated.h"

USTRUCT(BlueprintType)
struct CITYMAKER_API FBasePointCloud
{
	GENERATED_BODY()

public:
	FBasePointCloud() :
		Transform(FTransform::Identity),
		Name("")
		{};

	UPROPERTY(BlueprintReadWrite)
	FTransform Transform;
	UPROPERTY(BlueprintReadWrite)
	FString Name;

	bool ParseFromPreparedALembic(int32 PointIndex, const TArray<FTransform>& Transforms,
		const TMap<FString, TArray<FString>>& MetaDatas);
};



USTRUCT(BlueprintType)
struct CITYMAKER_API FCityPointClouds
{
	GENERATED_BODY()

public:
	void Clear();

	UPROPERTY(BlueprintReadWrite)
	TArray<FBasePointCloud> BasePoints;
};