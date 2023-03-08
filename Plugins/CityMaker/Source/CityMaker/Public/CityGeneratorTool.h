// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CityGeneratorDataTypes.h"
#include "CityGeneratorTool.generated.h"

UCLASS()
class CITYMAKER_API ACityGeneratorTool : public AActor
{
	GENERATED_BODY()
	
	friend class ACityGeneratorManager;

public:	
	ACityGeneratorTool();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	virtual bool IsEditorOnly() const override;
	
	virtual void AddSelf(CityTableDescriptor& Desc) const;
};
