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

	//Level choose options ....
	//MainLevel loading off map -> GameModeBase -> spawn timer and
	//Setting up all of actors
	//Spawn in code some actors based on map
	
	UPROPERTY(EditAnywhere, Category = "LevelSettings")
	int MaxPointsToGather;
	UPROPERTY(EditAnywhere, Category = "LevelSettings")
	int CurrentGatheredPoints;

	UPROPERTY(EditAnywhere, Category="Image Level Data")
	FUImageLevelData ImageLevelInfo;
};
