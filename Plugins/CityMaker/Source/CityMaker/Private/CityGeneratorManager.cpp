// Fill out your copyright notice in the Description page of Project Settings.


#include "CityGeneratorManager.h"
#include "CityGeneratorTool.h"
#include <EngineUtils.h>
#include <FileHelper.h>
#include <json.h>

const FString RoadHeader = "---,Position_x,Position_y,Position_z\n";

ACityGeneratorManager::ACityGeneratorManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ACityGeneratorManager::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ACityGeneratorManager::IsEditorOnly() const
{
	return true;
}

void ACityGeneratorManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACityGeneratorManager::PrepareCSVHeaders(CityTableDescriptor& Desc) const
{
	Desc.RoadsAttribute.Reserve(1000);
	Desc.RoadsAttribute = RoadHeader;
}

void ACityGeneratorManager::PrepareDataTable() const
{
	CityTableDescriptor CityDesc;
	PrepareCSVHeaders(CityDesc);
	
 	for(TActorIterator<ACityGeneratorTool> It(GetWorld()); It; ++It)
 	{
 		if (*It && IsValid(*It))
 		{
 			It->AddSelf(CityDesc);
 		}
 	}

	FFileHelper::SaveStringToFile(CityDesc.RoadsAttribute, *Path);
}

