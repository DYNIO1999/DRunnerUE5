#pragma once

#include "CoreMinimal.h"
//Platforms NONE (BLACK) = (NONE, NONE, NONE) (0, 0, 0)

UENUM(BlueprintType) 
enum class EGamePlatformType : uint8
{
	None = 255  UMETA(DisplayName = "None"),
	Standard = 0 UMETA(DisplayName = "Standard"),
	Ascending = 10 UMETA(DisplayName = "Ascending"),
	Descending = 20 UMETA(DisplayName = "Descending"),
};

UENUM(BlueprintType) 
enum class EGamePlatformDirection : uint8
{
	None = 255 UMETA(DisplayName = "None"),
	Forward = 0 UMETA(DisplayName = "Forward"),
	Backward =  10 UMETA(DisplayName = "Backward"),
	Right =  20 UMETA(DisplayName = "Right"),
	Left = 30 UMETA(DisplayName = "Left")
	
};

UENUM(BlueprintType) 
enum class EGamePlatformMovementType : uint8
{
	None = 255 UMETA(DisplayName = "None"),
	Running = 0 UMETA(DisplayName = "Running"),
	Walking = 10 UMETA(DisplayName = "Walking"),
};


static EGamePlatformType CheckPlatformType(const uint8 Value)
{
	EGamePlatformType PlatformTypeVal; 
	switch (Value) {  
	case static_cast<int>(EGamePlatformType::None):
		PlatformTypeVal= EGamePlatformType::None;
			break;
	case static_cast<int>(EGamePlatformType::Standard):
		PlatformTypeVal= EGamePlatformType::Standard;
		break;

	case static_cast<int>(EGamePlatformType::Ascending):
		PlatformTypeVal= EGamePlatformType::Ascending;
		break;

	case static_cast<int>(EGamePlatformType::Descending):
		PlatformTypeVal= EGamePlatformType::Descending;
		break;

	default:
		PlatformTypeVal= EGamePlatformType::None;
			break;
			
	}
	return PlatformTypeVal;
}
static EGamePlatformDirection CheckPlatformDirection(const uint8 Value)
{
	EGamePlatformDirection PlatformDirection; 
	switch (Value) {  
	case static_cast<int>(EGamePlatformDirection::Forward):
		PlatformDirection= EGamePlatformDirection::Forward;
		break;
	case static_cast<int>(EGamePlatformDirection::Backward):
		PlatformDirection= EGamePlatformDirection::Backward;
		break;
	case static_cast<int>(EGamePlatformDirection::Right):
		PlatformDirection= EGamePlatformDirection::Right;
		break;
	case static_cast<int>(EGamePlatformDirection::Left):
		PlatformDirection= EGamePlatformDirection::Left;
		break;
	default:
		PlatformDirection= EGamePlatformDirection::None;
		break;
			
	}
	return PlatformDirection;
}

static EGamePlatformMovementType CheckPlatformMovementType(const uint8 Value)
{
	EGamePlatformMovementType PlatformMovementType; 
	switch (Value) {  

		case static_cast<int>(EGamePlatformMovementType::Walking):

		PlatformMovementType= EGamePlatformMovementType::Walking;
		break;

		case static_cast<int>(EGamePlatformMovementType::Running):

		PlatformMovementType= EGamePlatformMovementType::Running;
		break;
	
		default:
		PlatformMovementType= EGamePlatformMovementType::None;
		break;
			
	}
	return PlatformMovementType;
}