// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FXmlNode;

/**
 * 
 */
class CITYMAKER_API OSM_Parser
{
public:
	static void ParseFile(const FString& FilePath);
};
