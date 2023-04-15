// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "TestBFL.generated.h"

class UHoudiniAssetComponent;

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


/**
 * 
 */
UCLASS()
class CITYMAKER_API UTestBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static bool ReimportDataTable(UDataTable* DataTable, const FString& CSVFilePath);

	UFUNCTION(BlueprintCallable)
	static void ForceRecookHoudiniAsset(UHoudiniAssetComponent* Comp);
};
