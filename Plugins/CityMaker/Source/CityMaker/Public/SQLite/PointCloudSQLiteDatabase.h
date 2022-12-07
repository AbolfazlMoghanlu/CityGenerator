// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PointCloudTypes.h"

class CITYMAKER_API PointCloudSQLiteDatabase
{
public:
	
	PointCloudSQLiteDatabase();

	void InitTempFile();

	bool CLearAndInsertRoadPoints(const TArray<FRoadPointCloud>& RoadPoints);

	struct sqlite3* db;
};
