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


PointCloudSQLiteDatabase::PointCloudSQLiteDatabase()
{
	InitTempFile();
}

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
	// position_x, position_y, position_z, scale_x, scale_y, scale_z, pitch, roll, yaw, batch index
	SQL_EXEC("CREATE TABLE IF NOT EXISTS Road("
		"position_x FLOAT, position_y FLOAT, position_z FLOAT,"
		"scale_x FLOAT, scale_y FLOAT, scale_z FLOAT,"
		"pitch FLOAT, roll FLOAT, yaw FLOAT,"
		"batch_index INT"
		");");
	ERROR_CHECK("failed to create roads table!");
}

bool PointCloudSQLiteDatabase::CLearAndInsertRoadPoints(const TArray<FRoadPointCloud>& RoadPoints)
{
	FString Command;
	int result;
	char* err;

	// @todo: clear road table

	for (const FRoadPointCloud& Point : RoadPoints)
	{
		Command = FString::Printf(TEXT("INSERT INTO Road VALUES ("
			"%f, %f, %f," // location 
			"%f, %f, %f," // scale
			"%f, %f, %f," // rotation
			"%i"		  // batch index
			")"
			),
			Point.Transform.GetLocation().X, Point.Transform.GetLocation().Y, Point.Transform.GetLocation().Z,
			Point.Transform.GetScale3D().X, Point.Transform.GetScale3D().Y, Point.Transform.GetScale3D().Z,
			Point.Transform.Rotator().Pitch, Point.Transform.Rotator().Roll, Point.Transform.Rotator().Yaw,
			Point.BatchIndex);

		result = sqlite3_exec(db, TCHAR_TO_ANSI(*Command), 0, 0, &err);

		ERROR_CHECK("failed to insert road points!");

		if (result != SQLITE_OK)
		{
			return false;
		}
	}

	return true;
}

void PointCloudSQLiteDatabase::GetRoadsInSameBatch(int32 BatchIndex, TArray<FRoadPointCloud>& RoadPoints)
{
	RoadPoints.Empty();

	FString Command;
	sqlite3_stmt* stmt;

	Command = "SELECT position_x, position_y, position_z, scale_x, scale_y, scale_z,"
		"pitch, roll, yaw, batch_index FROM Road WHERE batch_index = " + FString::FromInt(BatchIndex);

	sqlite3_prepare_v2(db, TCHAR_TO_ANSI(*Command), -1, &stmt, 0);

	// @TODO: find a better way of counting elements
	int count = 0;
	while (sqlite3_step(stmt) != SQLITE_DONE) { count++; }

	RoadPoints.SetNumUninitialized(count);

	sqlite3_prepare_v2(db, TCHAR_TO_ANSI(*Command), -1, &stmt, 0);

	int index = 0;
	while (sqlite3_step(stmt) != SQLITE_DONE)
	{
		float p_x = float(sqlite3_column_double(stmt, 0));
		float p_y = float(sqlite3_column_double(stmt, 1));
		float p_z = float(sqlite3_column_double(stmt, 2));
	
		float s_x = float(sqlite3_column_double(stmt, 3));
		float s_y = float(sqlite3_column_double(stmt, 4));
		float s_z = float(sqlite3_column_double(stmt, 5));
	
		float r_x = float(sqlite3_column_double(stmt, 6));
		float r_y = float(sqlite3_column_double(stmt, 7));
		float r_z = float(sqlite3_column_double(stmt, 8));
	
		int batch_index = sqlite3_column_int(stmt, 9);
	
		RoadPoints[index].Transform = FTransform(
			FRotator(r_x, r_z, r_y), FVector(p_x, p_y, p_z), FVector(s_x, s_y, s_z));
	
		RoadPoints[index].BatchIndex = batch_index;

		index++;
	}
}

#undef SQL_EXEC
#undef ERROR_CHECK