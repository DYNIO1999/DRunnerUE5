#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGamePlatformEnums.h"
#include "Materials/MaterialInterface.h"
#include "DGameInstance.h"
#include "DRopeBridgePlatform.generated.h"

class UStaticMeshComponent;
class UCableComponent;
class USphereComponent;
class UDLoggingComponent;


UCLASS()
class DRUNNER_API ADRopeBridgePlatform : public AActor
{
	GENERATED_BODY()
	
public:
	
	ADRopeBridgePlatform();

	void InitializePlatform(
			const EGamePlatformType PlatformTypePar,
			const EGamePlatformDirection PlatformDirectionPar,
			const EGamePlatformMovementType MovementTypePar);

	UPROPERTY(EditAnywhere, Category = "Rope Bridge")
	UMaterialInterface* RopeMaterialReference;
	
	UPROPERTY(EditAnywhere, Category = "Logging")
	bool CanProduceLog;

	UPROPERTY(EditAnywhere, Category = "Rope Bridge")
	float WindSpeed;
	
	UPROPERTY(EditAnywhere, Category = "Rope Bridge")
	float RotationCooldown;
	
	UPROPERTY(EditAnywhere, Category = "Rope Bridge")
	FVector WindDirection;
	
	UPROPERTY(EditAnywhere, Category = "Rope Bridge")
	UStaticMesh* PlankMeshReference;

	UPROPERTY(EditAnywhere, Category = "Rope Bridge")
	float RopeGravityScale;
	
	UPROPERTY(EditAnywhere, Category = "Rope Bridge")
	int NumberOfPlanks;
	
	UPROPERTY(EditAnywhere, Category = "Rope Bridge")
	float HeightOffset;
	
	UPROPERTY(EditAnywhere, Category = "Rope Bridge")
	float SpaceBetweenPlanks;
	
	UPROPERTY(EditAnywhere, Category="Rope Bridge")
	UStaticMeshComponent* MeshToCheckCollision;
	
	UPROPERTY(EditAnywhere, Category="Rope Bridge")
	UStaticMeshComponent* BridgeStart;

	UPROPERTY(EditAnywhere, Category="Rope Bridge")
	UStaticMeshComponent* BridgeEnd;

	UPROPERTY(EditAnywhere, Category="Rope Bridge")
	TArray<UStaticMeshComponent*> BridgePlanksMeshComponents;

	
	UPROPERTY(EditAnywhere, Category="Rope Bridge")
	TArray<UCableComponent*> Ropes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="LogComponent")
	UDLoggingComponent* LogComponent;

	UPROPERTY(VisibleAnywhere, Category = "Rope Bridge")
	USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere, Category = "Type Platform")
	EGamePlatformType PlatformType;

	UPROPERTY(EditAnywhere, Category = "Type Platform")
	EGamePlatformDirection PlatformDirection;

	UPROPERTY(EditAnywhere, Category = "Type Platform")
	EGamePlatformMovementType PlatformMovementType;
	
	UPROPERTY()
	FTimerHandle LoggingCooldown;

	UPROPERTY()
	FTimerHandle SwapRotationTimer;

	void ProduceLog();
	
	UPROPERTY(EditAnywhere, Category = "Logging Delay")
	float LoggingDelayInSeconds;
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION()
	void SwapRotation();

	UPROPERTY()
	UDGameInstance* GameInstanceRef;
};
