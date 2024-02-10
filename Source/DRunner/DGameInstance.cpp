#include "DGameInstance.h"

UDGameInstance::UDGameInstance()
{
	MaxPointsToGather = 0;
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
}
