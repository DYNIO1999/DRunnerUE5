#include "DGameInstance.h"
#include "EventManager.h"

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

	
	GatheredFromDirection = EGameGatheredFromDirection::Unspecified;
	CurrentCoinId = 0;

	CurrentMap = EGameMaps::TestMap;

	TrackingTimeOfHMD = 0.0f;
	GamePlayTimePerMap = 0.0f;
}

void UDGameInstance::Init()
{
	Super::Init();

	UEventManager::CoinGatheredFromDirectionDelegate.AddDynamic(this, &UDGameInstance::GetGatheredCoinDirection);	
	
}

void UDGameInstance::ResetCoinDirectionAndID()
{
	CurrentCoinId = 0;
	GatheredFromDirection = EGameGatheredFromDirection::Unspecified;

}

void UDGameInstance::GetGatheredCoinDirection(EGameGatheredFromDirection GatheredDir, int32 CoinID)
{
	GatheredFromDirection = GatheredDir;
	CurrentCoinId = CoinID;
}

