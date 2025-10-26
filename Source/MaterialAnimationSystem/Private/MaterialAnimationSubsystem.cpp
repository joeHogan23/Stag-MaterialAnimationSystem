// Copyright (c) 2024 That Strange Creature & Joseph Sierejko. All rights reserved.

#include "MaterialAnimationSubsystem.h"

#include "MaterialAnimationSystem.h"
#include "Engine/World.h"
#include "Materials/MaterialParameterCollectionInstance.h"

void UMaterialAnimationSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	GlobalMaterialParameterCollection = FMaterialAnimationSystemModule::GetSettings().GetGlobalMaterialParameterCollection(InWorld);
	WorldTimeSecondsParam = FMaterialAnimationSystemModule::GetSettings().GetWorldTimeSecondsParam();
}


bool UMaterialAnimationSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
#if UE_EDITOR
	if(const UWorld* World = GetWorld())
		return World->IsNetMode(NM_Client);
#elif UE_SERVER
	return false;
#endif
	return true;
}

TStatId UMaterialAnimationSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UMaterialAnimationSubsystem, STATGROUP_Tickables);
}

void UMaterialAnimationSubsystem::Tick(float DeltaTime)
{
	if(const UWorld* World = GetWorld(); IsValid(World))
	{
		if(IsValid(GlobalMaterialParameterCollection))
		{
			GlobalMaterialParameterCollection->SetScalarParameterValue(FMaterialAnimationSystemModule::GetSettings().GetWorldTimeSecondsParam(), World->GetRealTimeSeconds());	
		}
	}
}