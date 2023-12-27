// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DMainGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DRUNNER_API ADMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	//get data from game-instance
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Image File Name")
	FString ImageFileName;
	
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void StartPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Maximum Coins")
	int MaxCoinsOnLevel;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Current Amount Coins")
	int CurrentGatheredCoins;


	UFUNCTION()
	void CoinCollected();


	
	
};
