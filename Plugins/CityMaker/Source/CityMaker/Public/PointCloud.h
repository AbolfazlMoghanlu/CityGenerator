// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PointCloudTypes.h"
#include "PointCloudConfig.h"
#include "PointCloud.generated.h"

//UCLASS(Abstract, BlueprintType, hidecategories = (Object))
UCLASS(BlueprintType, hidecategories = (Object))
class CITYMAKER_API UPointCloud : public UObject
{
	GENERATED_BODY()

public:
	UPointCloud(){};
	~UPointCloud(){};

	bool LoadFromAlembic(const FString& ProjectRelativePath, TArray<FTransform>& PreparedTransforms,
		TArray<FString>& MetadataColumnNames, TMap<FString, TArray<FString>>& MetadataValues,
		TMap<FString, FString>& DetailMetadataValues);

	UFUNCTION(BlueprintCallable)
	bool LoadRoadPointsFromAlembic(const FString& ProjectRelativePath);

	//UFUNCTION(BlueprintCallable)
	//void InitDB();

	UFUNCTION(BlueprintPure)
	FCityData& GetData();

	//UFUNCTION(BlueprintCallable)
	//void GetRoadsInSameBatch(int32 BatchIndex, TArray<FRoadPointCloud>& RoadPoints);

private:

	//PointCloudSQLiteDatabase DB;

	FCityData CityData;
};
