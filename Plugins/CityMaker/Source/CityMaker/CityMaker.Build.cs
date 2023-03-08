// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CityMaker : ModuleRules
{
	public CityMaker(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				ModuleDirectory + "/Public",
				PluginDirectory + "/../HoudiniEngine/Source/HoudiniEngineRuntime/Public",
            }
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				ModuleDirectory + "/Private",
				PluginDirectory + "/../HoudiniEngine/Source/HoudiniEngineRuntime/Private",
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Projects",
                "Engine",
                "CoreUObject",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "AlembicLib",
                "HoudiniEngineRuntime"
            }
            );
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);

        if (Target.bBuildEditor == true)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                        "UnrealEd"
                }
            );
        }
    }
}
