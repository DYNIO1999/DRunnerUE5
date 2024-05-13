#pragma once

#include "CoreMinimal.h"
#include "DGamePlatformEnums.h"
#include "GameFramework/Actor.h"
#include "DCoin.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class DRUNNER_API ADCoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADCoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void Initialize(const int32 ID, const EGamePlatformType PlatformTypePar, const EGamePlatformDirection PlatformDirectionPar);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventTriggered,float, MultiplayerGainPerPoint);
	
	UPROPERTY(BlueprintAssignable, Category = "EventGathered")
	FOnEventTriggered OnEventGathered;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Limit")
	float AllowedOffsetLimit;


	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> SphereComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void SendInfoGathered(const float MultiplayerPerPoint) const;

	UPROPERTY()
	int32 CoinID;

	UPROPERTY()
	FVector ForwardDirectionBasedOnPlatform;

	UPROPERTY()
	EGamePlatformType PlatformType;
	UPROPERTY()
	EGamePlatformDirection PlatformDirection;
	
};
