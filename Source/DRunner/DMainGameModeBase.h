#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DGamePlatformEnums.h"
#include "GameFramework/PlayerController.h"
#include "DMainGameModeBase.generated.h"



USTRUCT(BlueprintType)
struct FPlatformDefinition
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGamePlatformType PlatformType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGamePlatformDirection PlatformDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EGamePlatformMovementType MovementType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AlreadySet;
	
	FPlatformDefinition() = default;
	
	FPlatformDefinition(const EGamePlatformType Type, const EGamePlatformDirection Direction, const EGamePlatformMovementType Movement)
		: PlatformType(Type), PlatformDirection(Direction), MovementType(Movement), AlreadySet(false) {}
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platforms Actors")
	TSubclassOf<AActor> RopeBridgePlatformRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Platforms Actors")
	TSubclassOf<AActor> EndPointPlatformRef;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Image File Name")
	FString ImageFileName;
	
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void StartPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Maximum Coins")
	float MaxCoinsOnLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Current Amount Coins")
	float CurrentGatheredCoins;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="TestMode")
	bool RunningInTestMode;

	TSubclassOf<AActor> ChooseActorToSpawn(
		const EGamePlatformType PlatformTypePar,
			const EGamePlatformDirection PlatformDirectionPar,
			const EGamePlatformMovementType MovementTypePar);
	

	UFUNCTION(BlueprintCallable, Category = "Loading saved data")
	void UpdatedCollectedAndPosition(FVector PlayerPos, float NumberOfCoinsGathered);
    	
	UFUNCTION()
	void CoinCollected(float MultiplayerPerPoint);

	UFUNCTION()
	void HandleLoadingPlayerInfo();
	UFUNCTION()
	void HandleSavingPlayerInfo();
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventLoadedUpdateUI);
	
	UPROPERTY(BlueprintAssignable, Category = "Update UI")
	FOnEventLoadedUpdateUI OnEventLoadedUpdateUIDelegate;

	
	void SetPlayerStartLocation(float PlayerStartOffsetY);

	bool UpdatePlayerAfterLoading;
	
};
