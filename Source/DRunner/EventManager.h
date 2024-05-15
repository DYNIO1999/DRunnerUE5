#pragma once
#include  "DGamePlatformEnums.h"
#include "EventManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGenerateAudioGathered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPerformSavingPlayerInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPerformLoadingPlayerInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLostXRHeadsetTracking,FRotator, NewRotation);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDetectedCoinGatheredFromDirection, EGameGatheredFromDirection,GatheredFromDirection,int32, CoinID);


UCLASS()
class DRUNNER_API UEventManager : public UObject
{
	GENERATED_BODY()
public:
	static FGenerateAudioGathered PlaySoundGatheredDelegate;
	static FOnLostXRHeadsetTracking LostXRHeadsetTrackingDelegate;

	static FOnPerformSavingPlayerInfo PerformSavingPlayerInfoDelegate;
	static FOnPerformLoadingPlayerInfo PerformLoadingPlayerInfoDelegate;
	static FOnDetectedCoinGatheredFromDirection CoinGatheredFromDirectionDelegate;
};
