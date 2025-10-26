// Copyright (c) 2024 That Strange Creature & Joseph Sierejko. All rights reserved.


#include "MaterialAnimationSystemProjectSettings.h"

#include "MaterialAnimationSystem.h"
#include "Materials/MaterialParameterCollection.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Misc/ConfigCacheIni.h"

UMaterialParameterCollectionInstance* UMaterialAnimationSystemProjectSettings::GetGlobalMaterialParameterCollection(const UWorld& World) const
{
	if(GlobalMaterialParameterCollection.IsValid())
	{
		return World.GetParameterCollectionInstance(Cast<UMaterialParameterCollection>(Get()->GlobalMaterialParameterCollection.LoadSynchronous()));
	}
	return nullptr;
}

void UMaterialAnimationSystemProjectSettings::PostReloadConfig(FProperty* PropertyThatWasLoaded)
{
	Super::PostReloadConfig(PropertyThatWasLoaded);


}

void UMaterialAnimationSystemProjectSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FConfigFile ConfigFile;
	ConfigFile.Read(UKismetSystemLibrary::GetProjectDirectory()+ "Plugins/Content/MaterialAnimationSystem.ini");
}
