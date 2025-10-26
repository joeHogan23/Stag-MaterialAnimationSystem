// Copyright (c) 2024 That Strange Creature & Joseph Sierejko. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MaterialAnimationSystemTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MaterialAnimationGlobals.generated.h"

enum class EMaterialAnimationPlayMode : uint8;
class UMaterialInstanceDynamic;
/**
 * 
 */
UCLASS()
class MATERIALANIMATIONSYSTEM_API UMaterialAnimationGlobals : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static float PlayMaterialAnimation(const UObject* WorldContextObject, UPARAM(DisplayName="Material") UMaterialInstanceDynamic* MID, const FName AnimName, const
	                                   EMaterialAnimationPlayMode PlayMode = EMaterialAnimationPlayMode::Forward, const bool ForcePlay = false, const bool
	                                   InstantTransition = false);
	
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static float PlayMaterialAnimationForward(const UObject* WorldContextObject, UPARAM(DisplayName="Material") UMaterialInstanceDynamic* MID, const FName AnimName, const bool ForcePlay = false);

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static float PlayMaterialAnimationReverse(const UObject* WorldContextObject, UPARAM(DisplayName="Material") UMaterialInstanceDynamic* MID, const FName AnimName, const bool ForcePlay = false);

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static void PlayMultipleMaterialAnimations(UObject* WorldContextObject, UPARAM(DisplayName="Material") UMaterialInstanceDynamic* MID, const TArray<FName>& AnimNames, const EMaterialAnimationPlayMode PlayMode = EMaterialAnimationPlayMode::Forward, bool ForcePlay = false, bool Instant = false);

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static void PlayMultipleMaterialAnimationForward(UObject* WorldContextObject, UPARAM(DisplayName="Material") UMaterialInstanceDynamic* MID, const TArray<FName>& AnimNames, bool ForcePlay = false);

	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static void PlayMultipleMaterialAnimationReverse(UObject* WorldContextObject, UPARAM(DisplayName="Material") UMaterialInstanceDynamic* MID, const TArray<FName>& AnimNames, bool ForcePlay = false);

private:
	static float SetMaterialAnimationCurveParams_Internal(UMaterialInstanceDynamic* MID, const FName& AnimName, const EMaterialAnimationPlayMode PlayMode, const float WorldTimeSeconds, const bool ForcePlay, bool InstantTransition);
	
	static float GetWorldTimeSeconds(const UObject* WorldContextObject);
	static float GetWorldTimeAnimationOffset(UMaterialInstanceDynamic* MID, const FName& AnimName, EMaterialAnimationPlayMode PlayMode, const float WorldTime, float PreviousTime);
};
