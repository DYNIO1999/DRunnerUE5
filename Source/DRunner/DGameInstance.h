#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TestFunctions.h"
#include "DGameInstance.generated.h"



UCLASS()
class DRUNNER_API UDGameInstance : public UGameInstance
{
	GENERATED_BODY()

	
public:

	UDGameInstance();
	
	UPROPERTY(BlueprintReadWrite, Category = "LevelSettings")
	int MaxPointsToGather;
	UPROPERTY(BlueprintReadWrite, Category = "LevelSettings")
	int CurrentGatheredPoints;

	UPROPERTY(BlueprintReadWrite, Category="Image Level Data")
	FUImageLevelData ImageLevelInfo;

	UPROPERTY(BlueprintReadWrite, Category="Platform Offset")
	float PlatformConstantOffset{1100};

	UPROPERTY(BlueprintReadWrite, Category="Platform Time Limit")
	float TimeInSecondsPerPlatform;

	UPROPERTY(BlueprintReadWrite, Category="Player Status")
	bool  IsPlayerDead;
};
