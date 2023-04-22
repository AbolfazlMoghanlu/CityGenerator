// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <UnrealString.h>
#include "Engine/DataTable.h"
#include "CityGeneratorDataTypes.generated.h"

// as CSV
struct CityTableDescriptor
{
	FString RoadsAttribute;
	FString PedestrianLineAttributes;
};

struct FWay
{
	int64 ID;
	TArray<FVector> Points;

	FString Type		= "Unkown";
	FString Name		= "Unkown";
	FString NameEn		= "Unkown";
	FString OneWay		= "Unkown";
	FString Service		= "Unkown";
	FString MaxSpeed	= "Unkown";
};


USTRUCT(BlueprintType)
struct FRoadDesc : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Position_x;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Position_y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Position_z;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Separator;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString FillerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RoadScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InCutSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float OutCutSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString CurveMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString BufferMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString RightSidewalkModules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LeftSidewalkModules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LinesParameter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ObstaclesParameter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LeftSidewalkModule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString LeftSidewalkBounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString RightSidewalkModule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString RightSidewalkBounds;
};

USTRUCT(BlueprintType)
struct FPedestrianLineDesc : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Position_x;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Position_y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Position_z;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float LinesDistance;
};