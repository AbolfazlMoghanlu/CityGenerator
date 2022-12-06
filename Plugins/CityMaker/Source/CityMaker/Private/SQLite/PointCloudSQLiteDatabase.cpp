// Fill out your copyright notice in the Description page of Project Settings.

#include "PointCloudSQLiteDatabase.h"
#include "Misc/Paths.h"
#include "UnrealString.h"
#include "LogMacros.h"

#include "sqlite3.h"

const FString TempFilePath = FPaths::ConvertRelativePathToFull(
	FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("CityMaker/Binaries/Win64/TempPointCloud.db"))); 


void PointCloudSQLiteDatabase::InitTempFile()
{
	sqlite3_open(TCHAR_TO_ANSI(*TempFilePath), &db);

	char* er;
	int result = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Road(x FLOAT, y FLOAT, name varchar(100));", NULL, NULL, &er);

	if (er != SQLITE_OK)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed do to : %s"), ANSI_TO_TCHAR(er));
	}
}