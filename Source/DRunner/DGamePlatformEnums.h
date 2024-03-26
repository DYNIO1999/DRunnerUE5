#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType) 
enum class EGamePlatformType : uint8
{
	None = 255  UMETA(DisplayName = "None"),
	Standard = 0 UMETA(DisplayName = "Standard"),
	Ascending = 50 UMETA(DisplayName = "Ascending"),
	Descending = 100 UMETA(DisplayName = "Descending"),
	RightPlatform =  150 UMETA(DisplayName = "RightPlatform"),
	LeftPlatform = 175 UMETA(DisplayName = "LeftPlatform"),
	RopeBridgePlatform = 200 UMETA(DisplayName = "RopeBridgePlatform")
};

UENUM(BlueprintType) 
enum class EGamePlatformDirection : uint8
{
	None = 255 UMETA(DisplayName = "None"),
	Forward = 0 UMETA(DisplayName = "Forward"),
	Right =  50 UMETA(DisplayName = "Right"),
	Back = 100 UMETA(DisplayName = "Back"),
	Left = 250 UMETA(DisplayName = "Left")
};

UENUM(BlueprintType) 
enum class EGamePlatformMovementType : uint8
{
	None = 255 UMETA(DisplayName = "None"),
	Running = 0 UMETA(DisplayName = "Running"),
	Walking = 125 UMETA(DisplayName = "Walking"),
	SpawnPoint = 250 UMETA(DisplayName = "SpawnPoint")
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

	case static_cast<int>(EGamePlatformType::LeftPlatform):
		PlatformTypeVal= EGamePlatformType::LeftPlatform;
		break;

	case static_cast<int>(EGamePlatformType::RightPlatform):
		PlatformTypeVal= EGamePlatformType::RightPlatform;
		break;
	case static_cast<int>(EGamePlatformType::RopeBridgePlatform):
		PlatformTypeVal = EGamePlatformType::RopeBridgePlatform;
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
	case static_cast<int>(EGamePlatformDirection::Right):
		PlatformDirection= EGamePlatformDirection::Right;
		break;
	case static_cast<int>(EGamePlatformDirection::Left):
		PlatformDirection= EGamePlatformDirection::Left;
		break;
	case static_cast<int>(EGamePlatformDirection::Back):
		PlatformDirection= EGamePlatformDirection::Back;
		break;
	default:
		PlatformDirection= EGamePlatformDirection::None;
		break;
			
	}
	return PlatformDirection;
}

static float GetAngleBasedOnPlatformDirection(const EGamePlatformDirection Value)
{
	float Angle; 
	switch (Value) {  
	case EGamePlatformDirection::Forward:
		Angle= 0.0;
		break;
	case EGamePlatformDirection::Right:
		Angle = 90.0;
		break;
	case EGamePlatformDirection::Left:
		Angle = -90.0;
		break;
	case EGamePlatformDirection::Back:
		Angle = 180.0;
		break;
	default:
		Angle = 0.0;
		break;
			
	}
	return Angle;
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

		case static_cast<int>(EGamePlatformMovementType::SpawnPoint):

		PlatformMovementType= EGamePlatformMovementType::SpawnPoint;
		break;
	
		default:
		PlatformMovementType= EGamePlatformMovementType::None;
		break;
			
	}
	return PlatformMovementType;
}