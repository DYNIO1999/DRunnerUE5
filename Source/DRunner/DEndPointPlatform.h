// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGamePlatformEnums.h"
#include "DEndPointPlatform.generated.h"

class USphereComponent;

UCLASS()
class DRUNNER_API ADEndPointPlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADEndPointPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Type Platform")
	EGamePlatformType PlatformType;

	UPROPERTY(EditAnywhere, Category = "Type Platform")
	EGamePlatformDirection PlatformDirection;

	UPROPERTY(EditAnywhere, Category = "Type Platform")
	EGamePlatformMovementType PlatformMovementType;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> PortalEntranceMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> SphereComp;


	FTimerHandle OpenNewLevelDelay;

	
	virtual void Tick(float DeltaTime) override;

	void InitializePlatform(
		const EGamePlatformType PlatformTypePar,
		const EGamePlatformDirection PlatformDirectionPar,
		const EGamePlatformMovementType MovementTypePar);


	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void HandlePortalEntrance() const;
};
