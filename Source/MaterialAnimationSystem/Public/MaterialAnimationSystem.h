// Copyright (c) 2024 That Strange Creature & Joseph Sierejko. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "MaterialAnimationSystemProjectSettings.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMaterialAnimationSystem, Log, All);

class FMaterialAnimationSystemModule : public IModuleInterface
{
public:

	FMaterialAnimationSystemModule();
	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	static UMaterialAnimationSystemProjectSettings& GetSettings();

	static FMaterialAnimationSystemModule& Get();
	
protected:
	
	UMaterialAnimationSystemProjectSettings* GetProjectSettingsInstance() const;
	
private:
	void CreateProjectSettings();
	
	UMaterialAnimationSystemProjectSettings* ProjectSettings = nullptr;
};
