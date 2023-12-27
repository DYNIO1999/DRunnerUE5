// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DSpawnCoinComp.generated.h"

class ADCoin;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRUNNER_API UDSpawnCoinComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDSpawnCoinComp();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Coin To Spawn")
	TSubclassOf<AActor> ActorToSpawn;
	void SpawnCoinActor(const FTransform& NewCoinTransform);
	
};
