// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CityGeneratorTool.h"
#include "CityGeneratorDataTypes.h"
#include "RoadTool.generated.h"

class URoadDataAsset;
class UInstancedStaticMeshComponent;

USTRUCT(BlueprintType)
struct FRoadAttribs
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RoadScale = 1;
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
