// Copyright (c) 2024 That Strange Creature & Joseph Sierejko. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MaterialAnimationSystemTypes.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMaterialAnimationPlayMode : uint8
{
	Forward,
	Reverse
};

namespace FMaterialAnim
{
	inline EMaterialAnimationPlayMode ToEnum(const bool bForward)
	{
		return bForward ? EMaterialAnimationPlayMode::Forward : EMaterialAnimationPlayMode::Reverse;
	}
}