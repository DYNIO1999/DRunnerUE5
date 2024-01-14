// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "DPlayer.generated.h"

class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

UCLASS()
class DRUNNER_API ADPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(EditAnywhere, Category="Player VituSphere Movement")
	FVector PlayerVirtuSphereMovement;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEventTriggered);
	
	UPROPERTY(BlueprintAssignable, Category = "EventPlayerLost")
	FOnEventTriggered OnEventPlayerLost;

	UFUNCTION(BlueprintCallable, Category = "EventPlayerLost")
	void PlayerDead();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
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

	
	void Walk(const FInputActionValue& InputValue);
	void Look(const FInputActionValue& InputValue);
	void StartRunning();
	void StartJump();
	void StopRunning();

	UPROPERTY()
	FTimerHandle PlayerDataSavingTimer;

	void SavePlayerData();
	
private:
	UPROPERTY()
	float CurrentCharacterSpeed;

	
	UPROPERTY()
	TObjectPtr<UCharacterMovementComponent> CharacterMovementComp;


	void ChangeSpeedValue(float SpeedValue) const;

	
	
	//OnEventGathered.Broadcast();
};
