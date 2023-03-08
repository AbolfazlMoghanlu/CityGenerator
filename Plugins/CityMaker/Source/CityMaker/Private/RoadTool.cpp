// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadTool.h"
#include <Components/SplineComponent.h>

ARoadTool::ARoadTool()
{
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SetRootComponent(Spline);
}

void ARoadTool::AddSelf(CityTableDescriptor& Desc) const
{
	FString& RoadTable = Desc.RoadsAttribute;
	auto AddRoadAttrib = [&](int32 ix)
	{
		// RowName
		RoadTable.Append(GetName() + "_" + FString::FromInt(ix) + ",");

		// Position
		FVector Location = Spline->GetWorldLocationAtSplinePoint(ix);
		RoadTable.Append(FString::Printf(TEXT("%f, %f, %f,"), Location.X, Location.Y, Location.Z));

		RoadTable.Append("\n");
	};

	const int32 NumPt = Spline->GetNumberOfSplinePoints();
	for (int32 i = 0; i < NumPt; i++)
	{
		AddRoadAttrib(i);
	}

	//RoadTable.Append()
	
	//FString Out;
	//Out = "---,Position_x,Position_y,Position_z\n";
	//Out.Append("Na1, 0, 10, 0\n");
	//Out.Append("Na2, 30, 10, 0\n");
	//Out.Append("Na3, 0, 10, 50\n");
}