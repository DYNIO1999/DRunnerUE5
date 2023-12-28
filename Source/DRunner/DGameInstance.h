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
	
	UPROPERTY(EditAnywhere, Category = "LevelSettings")
	int MaxPointsToGather;
	UPROPERTY(EditAnywhere, Category = "LevelSettings")
	int CurrentGatheredPoints;

	UPROPERTY(EditAnywhere, Category="Image Level Data")
	FUImageLevelData ImageLevelInfo;

	UPROPERTY(EditAnywhere, Category="Platform Offset")
	float PlatformConstantOffset{1100};
};
