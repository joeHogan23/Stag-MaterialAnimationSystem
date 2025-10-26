// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MaterialAnimationSystem : ModuleRules
{
	public MaterialAnimationSystem(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new [] { "Core", "DeveloperSettings" });
			
		
		PrivateDependencyModuleNames.AddRange(
			new []
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
			}
			);
	}
}
