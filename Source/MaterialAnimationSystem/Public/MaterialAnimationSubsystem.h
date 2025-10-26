// Copyright (c) 2024 That Strange Creature & Joseph Sierejko. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "MaterialAnimationSubsystem.generated.h"

class UMaterialParameterCollectionInstance;
/**
 * 
 */
UCLASS(MinimalAPI)
class UMaterialAnimationSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	MATERIALANIMATIONSYSTEM_API virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	MATERIALANIMATIONSYSTEM_API virtual void Tick(float DeltaTime) override;

	bool ShouldCreateSubsystem(UObject* Outer) const final override;
	TStatId GetStatId() const final override;

private:
	UPROPERTY()
	FName WorldTimeSecondsParam;
	
	UPROPERTY()
	UMaterialParameterCollectionInstance* GlobalMaterialParameterCollection = nullptr;
};
