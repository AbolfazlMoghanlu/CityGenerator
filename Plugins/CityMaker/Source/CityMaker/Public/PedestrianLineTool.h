// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CityGeneratorTool.h"
#include "RoadDataAsset.h"
#include "PedestrianLineTool.generated.h"

/**
 * 
 */
UCLASS()
class CITYMAKER_API APedestrianLineTool : public ACityGeneratorTool
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPedestrianLineDataAsset* PedestrianLineData;


protected:
	virtual void AddSelf(CityTableDescriptor& Desc) const override;
	
private:
};
