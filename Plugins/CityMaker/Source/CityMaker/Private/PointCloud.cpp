// Fill out your copyright notice in the Description page of Project Settings.

#include "PointCloud.h"

#include "Algo/AnyOf.h"
#include "PointCloudAlembicHelpers.h"
#include "Paths.h"

#if WITH_EDITOR
THIRD_PARTY_INCLUDES_START
#include "Alembic/AbcGeom/All.h"
#include "Alembic/AbcCoreFactory/IFactory.h"
THIRD_PARTY_INCLUDES_END
#endif 


DEFINE_LOG_CATEGORY(PointCloudLog)

bool UPointCloud::LoadFromAlembic(const FString& ProjectRelativePath)
{
#if WITH_EDITOR

	/** Factory used to generate objects*/
	Alembic::AbcCoreFactory::IFactory Factory;
	Alembic::AbcCoreFactory::IFactory::CoreType CompressionType = Alembic::AbcCoreFactory::IFactory::kUnknown;
	/** Archive-typed ABC file */
	Alembic::Abc::IArchive Archive;
	/** Alembic typed root (top) object*/
	Alembic::Abc::IObject TopObject;

	Factory.setPolicy(Alembic::Abc::ErrorHandler::kQuietNoopPolicy);
	Factory.setOgawaNumStreams(12);

	const FString FilePath = FPaths::ConvertRelativePathToFull(
		FPaths::Combine(FPaths::ProjectDir(), ProjectRelativePath));

	// Extract Archive and compression type from file
	Archive = Factory.getArchive(TCHAR_TO_UTF8(*FilePath), CompressionType);
	if (!Archive.valid())
	{
		UE_LOG(PointCloudLog, Warning, TEXT("Failed to open %s: Not a valid Rule Processor Alembic file."), *FilePath);
		return false;
	}

	// Get Top/root object
	TopObject = Alembic::Abc::IObject(Archive, Alembic::Abc::kTop);
	if (!TopObject.valid())
	{
		UE_LOG(PointCloudLog, Warning, TEXT("Failed to import %s: Root not is not valid."), *FilePath);
		return false;
	}

	TArray<FTransform> PreparedTransforms;
	TArray<FString> MetadataColumnNames;
	TMap<FString, TArray<FString>> MetadataValues;
	ParseAlembicObject(TopObject, PreparedTransforms, MetadataColumnNames, MetadataValues);
	
	Points.Clear();

	const int32 PointNum = PreparedTransforms.Num();
	Points.BasePoints.SetNum(PointNum, true);

	for (int i = 0; i < PointNum; i++)
	{
		Points.BasePoints[i].Transform = PreparedTransforms[i];

		//auto a = MetadataValues.Find("name")->GetData()[i];
		//Points.BasePoints[i].Name = a;
	}


	return true;

#endif
	return false;
}

FCityPointClouds& UPointCloud::GetData()
{
	return Points;
}
