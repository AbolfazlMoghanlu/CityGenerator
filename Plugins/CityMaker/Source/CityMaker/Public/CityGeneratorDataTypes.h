// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <UnrealString.h>

// as CSV
struct CityTableDescriptor
{
	FString RoadsAttribute;
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