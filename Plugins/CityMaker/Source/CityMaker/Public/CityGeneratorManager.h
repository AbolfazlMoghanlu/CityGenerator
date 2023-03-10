// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CityGeneratorDataTypes.h"
#include "CityGeneratorManager.generated.h"

UCLASS()
class CITYMAKER_API ACityGeneratorManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ACityGeneratorManager();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void PrepareDataTable() const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Path;

	UFUNCTION(BlueprintCallable)
	void MakeRoadsFromOsmFile(const FString& FilePath);
	
protected:
	virtual void BeginPlay() override;

	virtual bool IsEditorOnly() const override;

private:
	void PrepareCSVHeaders(CityTableDescriptor& Desc) const;
};
