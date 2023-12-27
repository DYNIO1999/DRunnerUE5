#pragma once

#include "CoreMinimal.h"
//Platforms NONE (BLACK) = (NONE, NONE, NONE) (0, 0, 0)

UENUM(BlueprintType) 
enum class EGamePlatformType : uint8
{
	None = 0  UMETA(DisplayName = "None"),
	Standard = 10 UMETA(DisplayName = "Standard"),
	Ascending UMETA(DisplayName = "Ascending"),
	Descending UMETA(DisplayName = "Descending"),
};

UENUM(BlueprintType) 
enum class EGamePlatformDirection : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Forward = 10 UMETA(DisplayName = "Forward"),
	Backward =  20 UMETA(DisplayName = "Backward"),
	Right =  30 UMETA(DisplayName = "Right"),
	Left = 40 UMETA(DisplayName = "Left")
};

UENUM(BlueprintType) 
enum class EGamePlatformMovementType : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Walking = 10 UMETA(DisplayName = "Walking"),
	Running = 20 UMETA(DisplayName = "Runing"),
};



