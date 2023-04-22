// Fill out your copyright notice in the Description page of Project Settings.


#include "CityMakerHelperBFL.h"
#include "UnrealEd.h"
#include "Factories/ReimportDataTableFactory.h"
#include "HoudiniAssetComponent.h"

bool UCityMakerHelperBFL::ReimportDataTable(UDataTable* DataTable, const FString& InFilePath)
{
#if WITH_EDITOR
	if (!DataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("FillDataTableFromCSVFile - The DataTable is invalid."));
		return false;
	}

	if (!IFileManager::Get().FileExists(*InFilePath))
	{
		UE_LOG(LogTemp, Error, TEXT("FillDataTableFromCSVFile - The file '%s' doesn't exist."), *InFilePath);
		return false;
	}

	DataTable->AssetImportData->Update(InFilePath);
	UCSVImportFactory* ImportFactory = NewObject<UCSVImportFactory>();
	return ImportFactory->ReimportCSV(DataTable) == EReimportResult::Succeeded;
#else

	return true;
#endif
}

void UCityMakerHelperBFL::ForceRecookHoudiniAsset(UHoudiniAssetComponent* Comp)
{
	Comp->MarkAsNeedCook();
}
