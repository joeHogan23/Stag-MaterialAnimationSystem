// Copyright (c) 2024 That Strange Creature & Joseph Sierejko. All rights reserved.

#include "MaterialAnimationSystem.h"
#include "UObject/Package.h"

#if WITH_EDITOR
#include "ISettingsModule.h"
#endif WITH_EDITOR

#define LOCTEXT_NAMESPACE "FMaterialAnimationSystemModule"

DEFINE_LOG_CATEGORY(LogMaterialAnimationSystem);

FMaterialAnimationSystemModule::FMaterialAnimationSystemModule()
{
	ProjectSettings = nullptr;
}

void FMaterialAnimationSystemModule::StartupModule()
{
	CreateProjectSettings();
}

void FMaterialAnimationSystemModule::ShutdownModule()
{
#if WITH_EDITOR
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "MaterialAnimationSystem");
	}
#endif

	if(!GExitPurge)
	{
		ProjectSettings->RemoveFromRoot();
	}
	ProjectSettings = nullptr;
}

UMaterialAnimationSystemProjectSettings& FMaterialAnimationSystemModule::GetSettings()
{
	const FMaterialAnimationSystemModule& Module = IsInGameThread() ? Get() : FModuleManager::GetModuleChecked<FMaterialAnimationSystemModule>("MaterialAnimationSystem");
	UMaterialAnimationSystemProjectSettings* Settings = Module.GetProjectSettingsInstance();
	check(Settings)
	return *Settings;
}

FMaterialAnimationSystemModule& FMaterialAnimationSystemModule::Get()
{
	return FModuleManager::LoadModuleChecked<FMaterialAnimationSystemModule>("MaterialAnimationSystem");
}

UMaterialAnimationSystemProjectSettings* FMaterialAnimationSystemModule::GetProjectSettingsInstance() const
{
	return ProjectSettings;
}

void FMaterialAnimationSystemModule::CreateProjectSettings()
{
	ProjectSettings = NewObject<UMaterialAnimationSystemProjectSettings>(GetTransientPackage(), UMaterialAnimationSystemProjectSettings::StaticClass());
	check(ProjectSettings);
	ProjectSettings->AddToRoot();

	#if WITH_EDITOR
		if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
		{
			SettingsModule->RegisterSettings("Project", "Plugins", "MaterialAnimationSystem",
				NSLOCTEXT("MaterialAnimationSystemProjectSettings", "MaterialAnimationSystemName", "Material Animation System"),
				NSLOCTEXT("MaterialAnimationSystemProjectSettings", "MaterialAnimationSystemDescription", "Configure Global Material Animation Settings "),
				ProjectSettings);
		}
	#endif WITH_EDITOR
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMaterialAnimationSystemModule, MaterialAnimationSystem)