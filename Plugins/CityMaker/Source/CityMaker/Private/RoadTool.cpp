// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadTool.h"
#include <Components/SplineComponent.h>
#include "Components/InstancedStaticMeshComponent.h"
#include "RoadDataAsset.h"
#include "Kismet/KismetMathLibrary.h"

const FString StartIconPath = TEXT("/ Script / Engine.StaticMesh'/CityMaker/Icon/Road/SM_RoadStart_Icon.SM_RoadStart_Icon'");
const FString EndIconPath = TEXT("/ Script / Engine.StaticMesh'/CityMaker/Icon/Road/SM_RoadEnd_Icon.SM_RoadEnd_Icon'");
const FString DirectionIconPath = TEXT("/ Script / Engine.StaticMesh'/CityMaker/Icon/Road/SM_RoadDirection_Icon.SM_RoadDirection_Icon'");

ARoadTool::ARoadTool()
{
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SetRootComponent(Spline);

	UStaticMesh* StartMesh = static_cast<UStaticMesh*>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *StartIconPath));
	UStaticMesh* EndMesh = static_cast<UStaticMesh*>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *EndIconPath));
	UStaticMesh* DirectionMesh = static_cast<UStaticMesh*>(StaticLoadObject(UStaticMesh::StaticClass(), nullptr, *DirectionIconPath));

	StartIcon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Start Icon"));
	StartIcon->SetupAttachment(Spline);
	StartIcon->SetStaticMesh(StartMesh);
	StartIcon->SetHiddenInGame(true);

	EndIcon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("End Icon"));
	EndIcon->SetupAttachment(Spline);
	EndIcon->SetStaticMesh(EndMesh);
	EndIcon->SetHiddenInGame(true);

	DirectionIcon = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Direction Icon"));
	DirectionIcon->SetupAttachment(Spline);
	DirectionIcon->SetStaticMesh(DirectionMesh);
	DirectionIcon->SetHiddenInGame(true);
}

void ARoadTool::InitWay(const FWay& Way)
{
	for(FVector Point : Way.Points)
	{
		Spline->AddSplinePoint(Point, ESplineCoordinateSpace::World, false);
	}

	Spline->RemoveSplinePoint(1, false);
	Spline->RemoveSplinePoint(0, true);
	
	// Add tags
	ID = Way.ID;
	Type = Way.Type;
	Name = Way.Name;
	NameEn = Way.NameEn;
	bOneWay = Way.OneWay == "yes";
	Service = Way.Service;
	MaxSpeed = Way.MaxSpeed;
}

void ARoadTool::AddSelf(CityTableDescriptor& Desc) const
{
	if (!bReadyToUse)
	{
		return;
	}

	FString& RoadTable = Desc.RoadsAttribute;
	auto AddRoadAttrib = [&](int32 ix, const TArray<FRoadAttribs>& RoadAttribs)
	{
		// RowName
		RoadTable.Append(GetName() + "_" + FString::FromInt(ix) + ",");

		// Position
		FVector Location = Spline->GetWorldLocationAtSplinePoint(ix);
		RoadTable.Append(FString::Printf(TEXT("%f, %f, %f,"), ix != -1 ? Location.X : 0.0f,
			ix != -1 ? Location.Y : 0.0f, ix != -1 ? Location.Z : 0.0f));
		
		// Separator
		RoadTable.Append(FString::Printf(TEXT("%i,"), ix == -1 ? 1 : 0));
		
		UStaticMesh* BaseMesh = RoadData ? RoadData->BaseMesh : nullptr;
		FString BaseMeshRefrence = BaseMesh ? BaseMesh->GetPathName() : "None";
		RoadTable.Append((ix == -1 ? "None" : BaseMeshRefrence) + ",");

		UStaticMesh* FillerMesh = RoadData ? RoadData->FillerMesh : nullptr;
		FString FillerMeshRefrence = FillerMesh ? FillerMesh->GetPathName() : "None";
		RoadTable.Append((ix == -1 ? "None" : FillerMeshRefrence) + ",");

		float RoadScale = ix == -1 ? 0.0 : ix < RoadAttribs.Num() ? RoadAttribs[ix].RoadScale : 0.0; 
		RoadTable.Append(FString::Printf(TEXT("%f,"), RoadScale));

		float InCutSize = ix == -1 ? 0.0 : ix < RoadAttribs.Num() ? RoadAttribs[ix].InCutSize : 0.0;
		RoadTable.Append(FString::Printf(TEXT("%f,"), InCutSize));

		float OutCutSize = ix == -1 ? 0.0 : ix < RoadAttribs.Num() ? RoadAttribs[ix].OutCutSize : 0.0;
		RoadTable.Append(FString::Printf(TEXT("%f,"), OutCutSize));

		UMaterialInterface* CurveMaterial = RoadData ? RoadData->CurveMaterial : nullptr;
		FString CurveMaterialRefrence = CurveMaterial ? CurveMaterial->GetPathName() : "None";
		RoadTable.Append((ix == -1 ? "None" : CurveMaterialRefrence) + ",");

		UStaticMesh* BufferMesh = RoadData ? RoadData->BufferMesh : nullptr;
		FString BufferMeshRefrence = BufferMesh ? BufferMesh->GetPathName() : "None";
		RoadTable.Append((ix == -1 ? "None" : BufferMeshRefrence) + ",");

		FString RightSidewalkModuleString = "None";
		if (RightSidewalkData)
		{
			if (RightSidewalkData->SidewalkModules.Num() > 0)
			{
				RightSidewalkModuleString = "";

				for (UStaticMesh* Mesh : RightSidewalkData->SidewalkModules)
				{
					RightSidewalkModuleString.Append(Mesh->GetPathName());
					RightSidewalkModuleString.Append("@");
				}
			}	
		}

		RoadTable.Append((ix == -1 ? "None" : RightSidewalkModuleString) + ",");


		FString LeftSidewalkModuleString = "None"; 
		if (LeftSidewalkData)
		{
			if (LeftSidewalkData->SidewalkModules.Num() > 0)
			{
				LeftSidewalkModuleString = "";

				for (UStaticMesh* Mesh : LeftSidewalkData->SidewalkModules)
				{
					LeftSidewalkModuleString.Append(Mesh->GetPathName());
					LeftSidewalkModuleString.Append("@");
				}
			}
		}
		
		RoadTable.Append((ix == -1 ? "None" : LeftSidewalkModuleString) + ",");

		FString LineString = "";

		if (ix != -1)
		{
			if (RoadAttribs.Num() > ix)
			{
				const TArray<FLineDescription>& lines = RoadAttribs[ix].Lines;

				for (const FLineDescription& Line : lines)
				{
					if (Line.LineData)
					{
						FString LineBaseMesh = "None";
						if (Line.LineData->BaseMesh)
						{
							LineBaseMesh = Line.LineData->BaseMesh->GetPathName();
						}
						LineString.Append(LineBaseMesh);
						LineString.Append("%");
						
						FString Checker = Line.LineData->bChecker ? "1%" : "0%";
						LineString.Append(Checker);

						FString FillerMaterial = "None";
						if (Line.LineData->FillerMaterial)
						{
							FillerMaterial = Line.LineData->FillerMaterial->GetPathName();
						}
						LineString.Append(FillerMaterial);
						LineString.Append("%");

						LineString.Append(FString::Printf(TEXT("%f"), Line.LineData->Width));
						LineString.Append("%");

						LineString.Append(FString::Printf(TEXT("%f"), Line.LineData->Length));
						LineString.Append("%");
					}

					FString AnchorType = Line.AnchorType == ELineAnchorType::Left ? "Left" 
						: Line.AnchorType == ELineAnchorType::Center ? "Center" : "Right";
					LineString.Append(AnchorType);
					LineString.Append("%");

					FString DistanceFromAnchor = FString::Printf(TEXT("%f"), Line.DistanceFromAnchor);
					LineString.Append(DistanceFromAnchor);
					
					LineString.Append("@");
				}
			}
		}

		RoadTable.Append(LineString); 
		RoadTable.Append(",");


		FString ObstacleString = "";

		if (ix != -1)
		{
			if (RoadAttribs.Num() > ix)
			{
				const TArray<FObstacleDescription>& obstacles = RoadAttribs[ix].Obstacles;

				for (const FObstacleDescription& obstacle : obstacles)
				{
					if (obstacle.ObstacleData)
					{
						FString ObstacleBaseMesh = "None";
						if (obstacle.ObstacleData->Module)
						{
							ObstacleBaseMesh = obstacle.ObstacleData->Module->GetPathName();
						}
						ObstacleString.Append(ObstacleBaseMesh);
						ObstacleString.Append("%");

						ObstacleString.Append(FString::Printf(TEXT("%f"), obstacle.ObstacleData->BoundSize));
						ObstacleString.Append("%");

						ObstacleString.Append(FString::Printf(TEXT("%f"), obstacle.ObstacleData->InstanceDistance));
						ObstacleString.Append("%");

						FString MaintainLastInstance = obstacle.ObstacleData->bMaintainLastInstance ? "1%" : "0%";
						ObstacleString.Append(MaintainLastInstance);
					}

					FString AnchorType = obstacle.AnchorType == ELineAnchorType::Left ? "Left"
						: obstacle.AnchorType == ELineAnchorType::Center ? "Center" : "Right";
					ObstacleString.Append(AnchorType);
					ObstacleString.Append("%");

					FString DistanceFromAnchor = FString::Printf(TEXT("%f"), obstacle.DistanceFromAnchor);
					ObstacleString.Append(DistanceFromAnchor);
					ObstacleString.Append("%");

					FString UOffset = FString::Printf(TEXT("%f"), obstacle.UOffset);
					ObstacleString.Append(UOffset);
					ObstacleString.Append("%");

					FString ZOffset = FString::Printf(TEXT("%f"), obstacle.ZOffset);
					ObstacleString.Append(ZOffset);

					ObstacleString.Append("@");
				}
			}
		}

		RoadTable.Append(ObstacleString);

		RoadTable.Append("\n");
	};

	TArray<FRoadAttribs> RoadAttribs = Attributes;
	RoadAttribs.AddDefaulted();

	const int32 NumPt = Spline->GetNumberOfSplinePoints();
	for (int32 i = 0; i < NumPt; i++)
	{
		AddRoadAttrib(i, RoadAttribs);
	}

	// add separator
	AddRoadAttrib(-1, RoadAttribs);
}

void ARoadTool::PostRegisterAllComponents()
{
	Super::PostInitializeComponents();

	//const int32 NumPt = Spline->GetNumberOfSplinePoints();
	//
	//for(int32 i = 0; i < NumPt ; i++)
	//{
	//	Spline->SetSplinePointType(i, ESplinePointType::Linear, false);
	//}
	//
	//Spline->UpdateSpline();
	//
	//if (NumPt > 1)
	//{
	//	StartIcon->SetWorldLocation(Spline->GetWorldLocationAtSplinePoint(0));
	//	EndIcon->SetWorldLocation(Spline->GetWorldLocationAtSplinePoint(NumPt - 1));
	//}
	//
	//DirectionIcon->ClearInstances();
	//
	//if (NumPt > 1)
	//{
	//	for (int32 i = 0; i < NumPt - 1; i++)
	//	{
	//		FVector Location = Spline->GetWorldLocationAtSplinePoint(i);
	//		FVector Tangent = Spline->GetTangentAtSplinePoint(i, ESplineCoordinateSpace::World);
	//		FRotator Rotation = Tangent.ToOrientationRotator();
	//
	//		DirectionIcon->AddInstance(FTransform(Rotation, Location, FVector::OneVector), true);
	//	}
	//}
}

