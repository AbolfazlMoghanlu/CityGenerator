// Fill out your copyright notice in the Description page of Project Settings.

#include "CityGeneratorTool.h"

ACityGeneratorTool::ACityGeneratorTool()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ACityGeneratorTool::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ACityGeneratorTool::IsEditorOnly() const
{
	return true;
}

void ACityGeneratorTool::AddSelf(CityTableDescriptor& Desc) const
{
		
}

void ACityGeneratorTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

