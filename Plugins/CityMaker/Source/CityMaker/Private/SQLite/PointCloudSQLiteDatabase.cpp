// Fill out your copyright notice in the Description page of Project Settings.

#include "PointCloudSQLiteDatabase.h"
#include "Misc/Paths.h"
#include "UnrealString.h"
#include "LogMacros.h"

#include "sqlite3.h"

DEFINE_LOG_CATEGORY_STATIC(LogPointCloudSQLite, Log, Log);

#define SQL_EXEC(x)	result = sqlite3_exec(db, x, 0, 0, &err);

#define ERROR_CHECK(x) if(result != SQLITE_OK)	\
	{ UE_LOG(LogPointCloudSQLite, Error, TEXT("%s SQLite Error : %s"), TEXT(x), ANSI_TO_TCHAR(err)); } 


const FString TempFilePath = FPaths::ConvertRelativePathToFull(
	FPaths::Combine(FPaths::ProjectPluginsDir(), TEXT("CityMaker/Binaries/Win64/TempPointCloud.db")));


void PointCloudSQLiteDatabase::InitTempFile()
{
	sqlite3_open(TCHAR_TO_ANSI(*TempFilePath), &db);

	int result;
	char* err;

	// clear all data
	sqlite3_db_config(db, SQLITE_DBCONFIG_RESET_DATABASE, 1, 0);
	SQL_EXEC("VACUUM");
	ERROR_CHECK("failed to clear data base!");
	sqlite3_db_config(db, SQLITE_DBCONFIG_RESET_DATABASE, 0, 0);


	// road table row data
	// position_x, position_y, position_z, scale_x, scale_y, scale_z, pitch, roll, yaw
	SQL_EXEC("CREATE TABLE IF NOT EXISTS Road(position_x FLOAT, position_y FLOAT, position_z FLOAT,"
		"scale_x FLOAT, scale_y FLOAT, scale_z FLOAT, pitch FLOAT, roll FLOAT, yaw FLOAT);");
	ERROR_CHECK("failed to create roads table!");


	SQL_EXEC("insert into Road VALUES (1, 2, 3, 4, 5, 6, 7, 8, 9)");
	ERROR_CHECK("failed to insert!");
}

#undef SQL_EXEC
#undef ERROR_CHECK