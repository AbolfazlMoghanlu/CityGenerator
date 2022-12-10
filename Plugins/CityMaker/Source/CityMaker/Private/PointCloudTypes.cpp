// Fill out your copyright notice in the Description page of Project Settings.

#include "PointCloudTypes.h"

void FCityData::Clear()
{
	RoadData.Points.Empty();
	RoadData.BatchCount = -1;
}
