// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CityGeneratorTool.h"
#include "RoadTool.generated.h"

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

	UFUNCTION(BlueprintPure)
	USplineComponent* GetSplineComponent() {return Spline;}

protected:
	virtual void AddSelf(CityTableDescriptor& Desc) const override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	USplineComponent* Spline;

};
