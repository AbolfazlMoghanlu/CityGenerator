// Fill out your copyright notice in the Description page of Project Settings.

#include "PointCloudTypes.h"

bool FBasePointCloud::ParseFromPreparedALembic(int32 PointIndex, const TArray<FTransform>& Transforms,
	const TMap<FString, TArray<FString>>& MetaDatas)
{
	

	return true;
}

void FCityPointClouds::Clear()
{
	BasePoints.Empty();
}
