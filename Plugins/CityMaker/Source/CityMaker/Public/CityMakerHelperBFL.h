// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CityMakerHelperBFL.generated.h"

class UHoudiniAssetComponent;

/**
 * 
 */
UCLASS()
class CITYMAKER_API UCityMakerHelperBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static bool ReimportDataTable(UDataTable* DataTable, const FString& CSVFilePath);

	UFUNCTION(BlueprintCallable)
	static void ForceRecookHoudiniAsset(UHoudiniAssetComponent* Comp);
};
