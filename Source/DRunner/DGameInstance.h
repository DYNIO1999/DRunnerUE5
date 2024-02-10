#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TestFunctions.h"
#include "VirtuSphereClient/Public/VirtuSphereClientStructs.h"
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

	UPROPERTY(BlueprintReadWrite, Category="Motor State")
	TArray<FMotorStateEvent> CurrentMotorStateEvent;

	UPROPERTY(BlueprintReadWrite, Category="Controller State")
	FControllerStateEvent CurrentControllerStateEvent;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	FVector PlayerCurrentPosition;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	FVector PlayerCurrentVelocity;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	FRotator PlayerCurrentRotation;

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	float PlayerCurrentSpeed; 

	UPROPERTY(BlueprintReadWrite, Category="Player Stats")
	FVector SpherePoseEvent;
	
	TMap<int64, TArray<FMotorStateEvent>> SavedMotorStatesEvents;
};
