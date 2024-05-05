#pragma once

#include "EventManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGenerateAudioGathered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSavedPlayerInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoadPlayerInfo);

UCLASS()
class DRUNNER_API UEventManager : public UObject
{
	GENERATED_BODY()
public:
	
	static FGenerateAudioGathered PlaySoundGatheredDelegate;
	static FSavedPlayerInfo SavePlayerInfoDelegate;
	static FLoadPlayerInfo LoadPlayerInfoDelegate;  
};
