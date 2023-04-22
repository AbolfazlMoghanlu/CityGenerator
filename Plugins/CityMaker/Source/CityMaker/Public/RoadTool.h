// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CityGeneratorTool.h"
#include "CityGeneratorDataTypes.h"
#include "RoadTool.generated.h"

class URoadDataAsset;
class USidewalkDataAsset;
class ULineDataAsset;
class URoadObstacleDataAsset;
class USidewalkModuleDefinitionDataAsset;
class UInstancedStaticMeshComponent;

UENUM(BlueprintType)
enum class ELineAnchorType : uint8
{
	Left,
	Center,
	Right
};

USTRUCT(BlueprintType)
struct FLineDescription
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ULineDataAsset* LineData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ELineAnchorType AnchorType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DistanceFromAnchor = 50.0f;
};

USTRUCT(BlueprintType)
struct FObstacleDescription
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	URoadObstacleDataAsset* ObstacleData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ELineAnchorType AnchorType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DistanceFromAnchor = 50.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float UOffset = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ZOffset = 0.0f;
};

USTRUCT(BlueprintType)
struct FRoadAttribs
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RoadScale = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float InCutSize = 0.1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float OutCutSize = 0.9;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FLineDescription> Lines;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FObstacleDescription> Obstacles;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<USidewalkModuleDefinitionDataAsset*> RightSidewalks;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<USidewalkModuleDefinitionDataAsset*> LeftSidewalks;
};

/**
 * 
 */
UCLASS()
class CITYMAKER_API ARoadTool : public ACityGeneratorTool
{
	GENERATED_BODY()

public:
	ARoadTool();

	void InitWay(const FWay& Way);

	UFUNCTION(BlueprintPure)
	USplineComponent* GetSplineComponent() {return Spline;}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	URoadDataAsset* RoadData;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int64 ID;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Type;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString NameEn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bOneWay;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Service;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString MaxSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FRoadAttribs> Attributes;

	// ----------------------------------------------------

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* StartIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* EndIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInstancedStaticMeshComponent* DirectionIcon;


protected:
	virtual void AddSelf(CityTableDescriptor& Desc) const override;

	virtual void PostRegisterAllComponents() override;

	
private:
	UPROPERTY(EditDefaultsOnly)
	USplineComponent* Spline;


};
