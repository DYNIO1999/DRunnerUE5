// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "DGamePlatformEnums.h"
#include "DPlayer.generated.h"

class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
class USphereComponent;
class UAudioComponent;
class UDGameInstance;

UCLASS()
class DRUNNER_API ADPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ADPlayer();

protected:
	virtual void BeginPlay() override;

public:

	
	UFUNCTION()
	void PlayPickedUpCoinSound();
	
	UPROPERTY(EditAnywhere, Category="Player VituSphere Movement")
	FVector PlayerVirtuSphereMovement;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventTriggered);
	
	UPROPERTY(BlueprintAssignable, Category = "EventPlayerLost")
	FOnEventTriggered OnEventPlayerLost;

	UFUNCTION(BlueprintCallable, Category = "EventPlayerLost")
	void PlayerDead();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, Category="Movement Speed")
	float CharacterWalkSpeed;

	UPROPERTY(EditAnywhere, Category="Movement Speed")
	float CharacterRunningSpeed;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* DefaultInputMapping;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* InputLookMouse;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* InputRun;

	UPROPERTY(EditDefaultsOnly, Category="Camera Pitch Limit")
	float CameraPitchLimit;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* InputJump;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCameraComponent> CameraComp;
		
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* PlayerLeftLegAudio;

	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* PlayerRightLegAudio;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* PlayerPickedUpAudio;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Legs")
	EGameUsedLeg PlayerCurrentLeg;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Legs")
	EGamePlatformMovementType PreviousPlatformMovementType;

	void Walk(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	void StartRunning();
	void StartJump();
	void StopRunning();

	UPROPERTY()
	FTimerHandle PlayerDataSavingTimer;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Legs")
	float ChangeLegCooldown;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Legs")
	float WalkingLegCooldown;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Legs")
	float RunningLegCooldown;

	UPROPERTY()
	FTimerHandle ChangeLegCooldownTimer;
	
	void SavePlayerData();

	void ChangeLeg();

	UPROPERTY()
	UDGameInstance* DGameInstanceRef;
	
private:
	UPROPERTY()
	float CurrentCharacterSpeed;
	
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComp;
	
	void ChangeSpeedValue(float SpeedValue) const;
	
};
