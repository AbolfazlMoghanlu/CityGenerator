// Fill out your copyright notice in the Description page of Project Settings.


#include "PedestrianLineTool.h"

void APedestrianLineTool::AddSelf(CityTableDescriptor& Desc) const
{
	if (!bReadyToUse)
	{
		return;
	}
	
	FString& PedestrianLineTable = Desc.PedestrianLineAttributes;


	// RowName
	PedestrianLineTable.Append(GetName() + ",");

	// Position
	FVector Location = GetActorLocation();
	PedestrianLineTable.Append(FString::Printf(TEXT("%f, %f, %f,"), Location.X, Location.Y, Location.Z));

	UStaticMesh* BaseMesh = PedestrianLineData ? PedestrianLineData->BaseMesh : nullptr; 
	PedestrianLineTable.Append((BaseMesh ? BaseMesh->GetPathName() : "None") + ",");

	PedestrianLineTable.Append(FString::Printf(TEXT("%f"), PedestrianLineData ? PedestrianLineData->LinesDistance : 0.0));

	PedestrianLineTable.Append("\n");
}
