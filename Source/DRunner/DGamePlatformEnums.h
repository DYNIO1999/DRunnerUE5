#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType) 
enum class EGamePlatformType : uint8
{
	Standard UMETA(DisplayName = "Standard")
};

UENUM(BlueprintType) 
enum class EGamePlatformDirection : uint8
{
	Forward UMETA(DisplayName = "Forward"),
	Backward UMETA(DisplayName = "Backward"),
	Right UMETA(DisplayName = "Right"),
	Left UMETA(DisplayName = "Left")
};

UENUM(BlueprintType) 
enum class EGamePlatformMovementType : uint8
{
	Walking UMETA(DisplayName = "Walking"),
	Running UMETA(DisplayName = "Runing"),
};



