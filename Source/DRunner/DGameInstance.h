#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TestFunctions.h"
#include "VirtuSphereClient/Public/VirtuSphereClientStructs.h"
#include "DGamePlatformEnums.h"
#include "DGameInstance.generated.h"


UCLASS()
class DRUNNER_API UDGameInstance : public UGameInstance
{
	GENERATED_BODY()

	
public:

	UDGameInstance();

	virtual void Init() override;
	
	
	UPROPERTY(BlueprintReadWrite, Category = "LevelSettings")
	float MaxPointsToGather;
	UPROPERTY(BlueprintReadWrite, Category = "LevelSettings")
	float CurrentGatheredPoints;

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

	UPROPERTY(BlueprintReadWrite, Category = "Platform Foward Vector")
	float AngleToSwing;
	
	TMap<int64, TArray<FMotorStateEvent>> SavedMotorStatesEvents;

	UPROPERTY(BlueprintReadWrite)
	EGamePlatformType CurrentPlatformType;

	UPROPERTY(BlueprintReadWrite)
	FVector CurrentWindDirection;

	UPROPERTY(BlueprintReadWrite)
	float ChangeLegCooldown;

	UPROPERTY(BlueprintReadWrite)
	EGamePlatformMovementType CurrentPlatformMovementType;

	UPROPERTY(BlueprintReadWrite)
	EGameUsedLeg CurrentPlayerLeg;

	UPROPERTY(BlueprintReadWrite)
	EGameGatheredFromDirection GatheredFromDirection;

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentCoinId;


	UPROPERTY(BlueprintReadWrite)
	EGameMaps CurrentMap;
	
	void ResetCoinDirectionAndID();

	float TrackingTimeOfHMD;
	float GamePlayTimePerMap;
	
private:
	UFUNCTION()
	void GetGatheredCoinDirection(EGameGatheredFromDirection GatheredDir, int32 CoinID);
};
