// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "TestBFL.generated.h"

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
};
