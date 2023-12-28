// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGamePlatformEnums.h"
#include "DStandardPlatform.generated.h"

class UDSpawnCoinComp;
class USphereComponent;

UCLASS()
class DRUNNER_API ADStandardPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	ADStandardPlatform();
	

protected:
	virtual void BeginPlay() override;

public:	
	void InitializePlatform(
			const EGamePlatformType PlatformTypePar,
			const EGamePlatformDirection PlatformDirectionPar,
			const EGamePlatformMovementType MovementTypePar);
	
	UPROPERTY(EditAnywhere, Category = "Type Platform")
	EGamePlatformType PlatformType;

	UPROPERTY(EditAnywhere, Category = "Type Platform")
	EGamePlatformDirection PlatformDirection;

	UPROPERTY(EditAnywhere, Category = "Type Platform")
	EGamePlatformMovementType PlatformMovementType;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> CoinLocalisation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Coin Spawn Component")
	TObjectPtr<UDSpawnCoinComp> CoinSpawnComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> SphereComp;
	
	virtual void Tick(float DeltaTime) override;

};