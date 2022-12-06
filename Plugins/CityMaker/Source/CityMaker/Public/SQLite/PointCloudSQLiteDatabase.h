// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class CITYMAKER_API PointCloudSQLiteDatabase
{
public:
	
	void InitTempFile();

	struct sqlite3* db;
};
