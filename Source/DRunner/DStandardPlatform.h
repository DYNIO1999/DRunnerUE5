// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGamePlatformEnums.h"
#include "DStandardPlatform.generated.h"

class UDSpawnCoinComp;
class USphereComponent;
class UDLoggingComponent;
class UAudioComponent;

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
	
	UPROPERTY(EditAnywhere, Category = "Logging")
	bool CanProduceLog;
	
	UPROPERTY(EditAnywhere, Category = "Type Platform")
	EGamePlatformType PlatformType;

	UPROPERTY(EditAnywhere, Category = "Type Platform")
	EGamePlatformDirection PlatformDirection;

	UPROPERTY(EditAnywhere, Category = "Type Platform")
	EGamePlatformMovementType PlatformMovementType;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> CoinLocalisation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Coin Spawn Component")
	TObjectPtr<UDSpawnCoinComp> CoinSpawnComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LogComponent")
	TObjectPtr<UDLoggingComponent> LogComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> SphereComp;

	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* StandardPlatformAmbientSound;
	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY()
	FTimerHandle MyTimerHandle;

	void ProduceLog();
	
	UPROPERTY(EditAnywhere, Category = "Logging Delay")
	float LoggingDelayInSeconds;
};
