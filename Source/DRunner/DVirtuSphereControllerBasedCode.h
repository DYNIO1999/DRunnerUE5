#pragma once

#include "CoreMinimal.h"
#include "AVirtuSphereController.h"
#include "DGameInstance.h"
#include "DVirtuSphereControllerBasedCode.generated.h"

UCLASS()
class DRUNNER_API ADVirtuSphereControllerBasedCode : public AVirtuSphereController
{
	GENERATED_BODY()
	protected:
	virtual void BeginPlay() override;
    
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void OnConnected_Implementation() override;
    virtual void OnDisconnected_Implementation()  override;
    virtual void OnSpherePose_Implementation(FSpherePoseEvent event) override;
    virtual void OnControllerState_Implementation(FControllerStateEvent event) override;
    virtual void OnMotorState_Implementation(FMotorStateEvent event) override;

	public:
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category="Wind Direction")
	FVector WindDirection;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category="Wind Direction")
	float Angle;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite , Category="Wind Direction")
	float  SwingCooldown;

	UPROPERTY(BlueprintReadWrite)
	UDGameInstance* DGameInstance;
	
	UPROPERTY(BlueprintReadWrite)
	FSpherePoseEvent CurrentPoseEvent;

	UPROPERTY(BlueprintReadWrite, Category="Speed Ascending And Descending")
	float SpeedAscendingAndDescending{0.1};
	
	private:
	FTimerHandle AscendDelay;
	bool CanAscend{true};

	FTimerHandle DescendDelay;
	bool CanDescend{true};
	
	void PerformAscending();
	void PerformDescending();

	void PerformSwing();
	
	float MinimalVelocity =0.0f;
	float MaximumVelocity = 6.0f;
	
	bool IsMotorPowerEnabled;

	bool IsUsingUpAndDowMotor;

	FTimerHandle WindSwingTimer;

	bool IsOnRopeBridge;

	
	
};
