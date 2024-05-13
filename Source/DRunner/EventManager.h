#pragma once

#include "EventManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGenerateAudioGathered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLostXRHeadsetTracking,FRotator, NewRotation);

UCLASS()
class DRUNNER_API UEventManager : public UObject
{
	GENERATED_BODY()
public:
	
	static FGenerateAudioGathered PlaySoundGatheredDelegate;
	static FOnLostXRHeadsetTracking LostXRHeadsetTrackingDelegate;
};
