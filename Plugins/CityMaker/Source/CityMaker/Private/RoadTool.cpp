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
		RoadTable.Append(FString::Printf(TEXT("%f, %f, %f,"), ix != -1 ? Location.X : 0.0f,
			ix != -1 ? Location.Y : 0.0f, ix != -1 ? Location.Z : 0.0f));
		
		// Separator
		RoadTable.Append(FString::Printf(TEXT("%i"), ix == -1 ? 1 : 0));


		RoadTable.Append("\n");
	};

	const int32 NumPt = Spline->GetNumberOfSplinePoints();
	for (int32 i = 0; i < NumPt; i++)
	{
		AddRoadAttrib(i);
	}

	// add separator
	AddRoadAttrib(-1);
}