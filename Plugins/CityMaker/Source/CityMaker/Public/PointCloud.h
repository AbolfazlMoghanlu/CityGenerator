// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PointCloudTypes.h"
#include "PointCloudConfig.h"
#include "SQLite/PointCloudSQLiteDatabase.h"
#include "PointCloud.generated.h"

//UCLASS(Abstract, BlueprintType, hidecategories = (Object))
UCLASS(BlueprintType, hidecategories = (Object))
class CITYMAKER_API UPointCloud : public UObject
{
	GENERATED_BODY()

public:
	UPointCloud(){};
	~UPointCloud(){};

	//UFUNCTION(BlueprintCallable)
	bool LoadFromAlembic(const FString& ProjectRelativePath, TArray<FTransform>& PreparedTransforms,
		TArray<FString>& MetadataColumnNames, TMap<FString, TArray<FString>>& MetadataValues);

	UFUNCTION(BlueprintCallable)
	bool LoadRoadPointsFromAlembic(const FString& ProjectRelativePath);

	UFUNCTION(BlueprintCallable)
	void InitDB();

	UFUNCTION(BlueprintCallable)
	FCityPointClouds& GetData();

private:
	
	PointCloudSQLiteDatabase DB;

	FCityPointClouds Points;
};
