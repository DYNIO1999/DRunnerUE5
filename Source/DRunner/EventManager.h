#pragma once

#include "EventManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGenerateAudioGathered);

UCLASS()
class DRUNNER_API UEventManager : public UObject
{
	GENERATED_BODY()
public:
	
	static FGenerateAudioGathered PlaySoundGatheredDelegate;  
};
