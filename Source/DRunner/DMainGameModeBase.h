#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DGamePlatformEnums.h"
#include "GameFramework/PlayerController.h"
#include "DMainGameModeBase.generated.h"


UCLASS()
class DRUNNER_API ADMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	UPROPERTY()
	APlayerController* PlayerController;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platforms Actors")
	TSubclassOf<AActor> ForwardStandardPlatform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platforms Actors")
	TSubclassOf<AActor> LeftStandardPlatformActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platforms Actors")
	TSubclassOf<AActor> RightStandardPlatform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platforms Actors")
	TSubclassOf<AActor> AscendingPlatform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platforms Actors")
	TSubclassOf<AActor> DescendingPlatform;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Image File Name")
	FString ImageFileName;
	
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void StartPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Maximum Coins")
	int MaxCoinsOnLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Current Amount Coins")
	int CurrentGatheredCoins;

	TSubclassOf<AActor> ChooseActorToSpawn(
		const EGamePlatformType PlatformTypePar,
			const EGamePlatformDirection PlatformDirectionPar,
			const EGamePlatformMovementType MovementTypePar);
	

	UFUNCTION()
	void CoinCollected();
	
	void SetPlayerStartLocation(float PlayerStartOffsetY);
	
	
};
