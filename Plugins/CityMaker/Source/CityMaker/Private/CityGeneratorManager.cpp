// Fill out your copyright notice in the Description page of Project Settings.


#include "CityGeneratorManager.h"
#include "CityGeneratorTool.h"
#include <EngineUtils.h>
#include <FileHelper.h>
#include <json.h>

#include "OSM_Parser.h"


const FString RoadHeader = 
	"Name, Position_x, Position_y, Position_z, Separator, BaseMesh, FillerMesh, RoadScale, InCutSize, OutCutSize,"
	"CurveMaterial, BufferMesh, RightSidewalkModules, LeftSidewalkModules, LinesParameter\n";

const FString PedestrianLineHeader =
"Name, Position_x, Position_y, Position_z, BaseMesh, LinesDistance\n";

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

	Desc.PedestrianLineAttributes.Reserve(1000);
	Desc.PedestrianLineAttributes = PedestrianLineHeader;
}

void ACityGeneratorManager::PrepareDataTable(const FString& TempFileDirectory) const
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

	FString RoadFilePath = TempFileDirectory + "Roads.csv";
	FFileHelper::SaveStringToFile(CityDesc.RoadsAttribute, *RoadFilePath);

	FString PedestrianLineFilePath = TempFileDirectory + "PedestrianLines.csv";
	FFileHelper::SaveStringToFile(CityDesc.PedestrianLineAttributes, *PedestrianLineFilePath);
}

void ACityGeneratorManager::MakeRoadsFromOsmFile(const FString& FilePath)
{
	TArray<FWay> Ways;
	OSM_Parser::ParseFile(FilePath, Ways);

	UWorld* World = GetWorld();
	if (World && RoadClass)
	{
		for (const FWay& Way : Ways)
		{
			FActorSpawnParameters SpawnParams;

			ensure(Way.Points.Num() > 1);

			ARoadTool* Road = World->SpawnActor<ARoadTool>(RoadClass,
				Way.Points[0], FRotator::ZeroRotator, SpawnParams);

			Road->InitWay(Way);

			Road->Tags.Add(FName("Spawn"));

		}
	}

	
}

