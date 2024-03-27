#include "DGameInstance.h"

UDGameInstance::UDGameInstance()
{
	MaxPointsToGather = 10;
	CurrentGatheredPoints = 0;
	IsPlayerDead = false;

	CurrentMotorStateEvent = {};
	CurrentControllerStateEvent = {};

	PlayerCurrentPosition ={};
	PlayerCurrentRotation = {};
	PlayerCurrentSpeed = 0.0f;
	SpherePoseEvent = {};
	PlayerCurrentVelocity = {};

	SavedMotorStatesEvents={};
	CurrentWindDirection=FVector::Zero();
	
	CurrentPlatformType = EGamePlatformType::None;
}
