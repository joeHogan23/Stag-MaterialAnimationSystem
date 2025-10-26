// Copyright (c) 2024 That Strange Creature & Joseph Sierejko. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MaterialAnimationSystemProjectSettings.generated.h"

class UMaterialParameterCollectionInstance;
class UMaterialParameterCollection;
/**
 * 
 */
UCLASS(config = MaterialAnimationSystem, DefaultConfig)
class MATERIALANIMATIONSYSTEM_API UMaterialAnimationSystemProjectSettings : public UObject
{
	GENERATED_BODY()

public:
	static const UMaterialAnimationSystemProjectSettings* Get() { return GetDefault<UMaterialAnimationSystemProjectSettings>(); }
	
	UMaterialParameterCollectionInstance* GetGlobalMaterialParameterCollection(const UWorld& World) const;
	const FName& GetWorldTimeSecondsParam() const { return WorldTimeSecondsParam; }

	virtual void PostReloadConfig(FProperty* PropertyThatWasLoaded) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
private:
	UPROPERTY(EditAnywhere, Config)
	FName WorldTimeSecondsParam = FName("WorldTimeSeconds");
	
	UPROPERTY(EditAnywhere, Config, meta=(AllowedClasses="/Script/Engine.MaterialParameterCollection"))
	TSoftObjectPtr<UObject> GlobalMaterialParameterCollection = nullptr;
};
