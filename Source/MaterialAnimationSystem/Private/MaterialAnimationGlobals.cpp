// Copyright (c) 2024 That Strange Creature & Joseph Sierejko. All rights reserved.


#include "MaterialAnimationGlobals.h"

#include "Engine/World.h"
#include "Materials/MaterialInstanceDynamic.h"

float UMaterialAnimationGlobals::PlayMaterialAnimation(const UObject* WorldContextObject, UMaterialInstanceDynamic* MID, const FName AnimName, const EMaterialAnimationPlayMode PlayMode, const bool ForcePlay, const bool InstantTransition)
{
	if(IsValid(MID))
	{
		return SetMaterialAnimationCurveParams_Internal(MID, AnimName, PlayMode, GetWorldTimeSeconds(WorldContextObject), ForcePlay, InstantTransition);
	}
	return -1.f;
}

float UMaterialAnimationGlobals::PlayMaterialAnimationForward(const UObject* WorldContextObject, UMaterialInstanceDynamic* MID, const FName AnimName, const bool ForcePlay)
{
	if(IsValid(MID))
	{
		return SetMaterialAnimationCurveParams_Internal(MID, AnimName, EMaterialAnimationPlayMode::Forward, GetWorldTimeSeconds(WorldContextObject), ForcePlay, false);
	}
	return -1.f;
}

float UMaterialAnimationGlobals::PlayMaterialAnimationReverse(const UObject* WorldContextObject, UMaterialInstanceDynamic* MID, const FName AnimName, const bool ForcePlay)
{
	if(IsValid(MID))
	{
		return SetMaterialAnimationCurveParams_Internal(MID, AnimName, EMaterialAnimationPlayMode::Reverse, GetWorldTimeSeconds(WorldContextObject), ForcePlay, false);
	}
	return -1.f;
}

void UMaterialAnimationGlobals::PlayMultipleMaterialAnimations(UObject* WorldContextObject, UMaterialInstanceDynamic* MID, const TArray<FName>& AnimNames, const EMaterialAnimationPlayMode PlayMode, bool ForcePlay, bool Instant)
{
	if(IsValid(MID))
	{
		if(float WorldTimeSeconds = GetWorldTimeSeconds(WorldContextObject); WorldTimeSeconds > 0)
		{
			for(const FName& AnimName : AnimNames)
			{
				SetMaterialAnimationCurveParams_Internal(MID, AnimName, PlayMode, WorldTimeSeconds, ForcePlay, Instant);
			}
		}
	}
}

void UMaterialAnimationGlobals::PlayMultipleMaterialAnimationForward(UObject* WorldContextObject, UMaterialInstanceDynamic* MID, const TArray<FName>& AnimNames, bool ForcePlay)
{
	if(IsValid(MID))
	{
		if(const float WorldTimeSeconds = GetWorldTimeSeconds(WorldContextObject); WorldTimeSeconds > 0)
		{
			for(const FName& AnimName : AnimNames)
			{
				SetMaterialAnimationCurveParams_Internal(MID, AnimName, EMaterialAnimationPlayMode::Forward, WorldTimeSeconds, ForcePlay, false);
			}
		}
	}
}

void UMaterialAnimationGlobals::PlayMultipleMaterialAnimationReverse(UObject* WorldContextObject, UMaterialInstanceDynamic* MID, const TArray<FName>& AnimNames, bool ForcePlay)
{
	if(IsValid(MID))
	{
		if(const float WorldTimeSeconds = GetWorldTimeSeconds(WorldContextObject); WorldTimeSeconds > 0)
		{
			for(const FName& AnimName : AnimNames)
			{
				SetMaterialAnimationCurveParams_Internal(MID, AnimName, EMaterialAnimationPlayMode::Reverse, WorldTimeSeconds, ForcePlay, false);
			}
		}
	}
}

float UMaterialAnimationGlobals::SetMaterialAnimationCurveParams_Internal(UMaterialInstanceDynamic* MID, const FName& AnimName, const EMaterialAnimationPlayMode PlayMode, const float WorldTimeSeconds, const bool ForcePlay, bool InstantTransition)
{
	FLinearColor AnimParams = MID->K2_GetVectorParameterValue(AnimName);

	
	const float Direction = PlayMode == EMaterialAnimationPlayMode::Forward ? 1 : 0;

	//If the animation is 
	const float PreviousTime = FMath::IsNearlyEqual(AnimParams.A, 1.f) ? AnimParams.B : AnimParams.G;

	if(AnimParams.A != Direction || ForcePlay || InstantTransition)
	{
		AnimParams.A = Direction;

		if(!InstantTransition)
		{
			AnimParams.R = ForcePlay ? WorldTimeSeconds : GetWorldTimeAnimationOffset(MID, AnimName, PlayMode, WorldTimeSeconds, PreviousTime);
		}
		else
		{
			AnimParams.R = -1;
		}
	}
	MID->SetVectorParameterValue(AnimName, AnimParams);
	return PlayMode == EMaterialAnimationPlayMode::Forward ? AnimParams.G : AnimParams.B;
}

float UMaterialAnimationGlobals::GetWorldTimeSeconds(const UObject* WorldContextObject)
{
	if(const UWorld* World = WorldContextObject->GetWorld())
	{
		return World->GetRealTimeSeconds();
	}
	return -1.f;
}

float UMaterialAnimationGlobals::GetWorldTimeAnimationOffset(UMaterialInstanceDynamic* MID, const FName& AnimName, const EMaterialAnimationPlayMode PlayMode, const float WorldTime, const float PreviousTime)
{
	const FLinearColor AnimParams = MID->K2_GetVectorParameterValue(AnimName);
	const float NewTime = PlayMode == EMaterialAnimationPlayMode::Forward ? AnimParams.B : AnimParams.G;

	if(NewTime == 0 || PreviousTime == 0)
		return WorldTime;
		
	const float Elapsed = WorldTime - AnimParams.R;
	const float TimeRemainingNormalized = 1 - FMath::Min(Elapsed / PreviousTime, 1.f);

	return WorldTime - (TimeRemainingNormalized * NewTime);
}
