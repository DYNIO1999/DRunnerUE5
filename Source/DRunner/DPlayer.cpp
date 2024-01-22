// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DGameInstance.h"
#include "DrawDebugHelpers.h"
// Sets default values
ADPlayer::ADPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");

	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ADPlayer::BeginPlay()
{
	Super::BeginPlay();

	CharacterMovementComp = GetCharacterMovement<UCharacterMovementComponent>();
	
	CurrentCharacterSpeed = CharacterWalkSpeed;
	CharacterMovementComp->MaxWalkSpeed = CurrentCharacterSpeed;
	GetWorldTimerManager().SetTimer(PlayerDataSavingTimer, this, &ADPlayer::SavePlayerData, 0.1f, true);
	
}

void ADPlayer::PlayerDead()
{
	OnEventPlayerLost.Broadcast();
}

// Called every frame
void ADPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const APlayerController* PlayerController = GetController<APlayerController>();

	const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	
	checkf(Subsystem,TEXT("Subsytem Ptr is nullptr!"));

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultInputMapping, 0);

	UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	InputComp->BindAction(InputMove, ETriggerEvent::Triggered, this, &ADPlayer::Walk);
	InputComp->BindAction(InputLookMouse, ETriggerEvent::Triggered, this, &ADPlayer::Look);
	InputComp->BindAction(InputRun, ETriggerEvent::Started, this, &ADPlayer::StartRunning);
	InputComp->BindAction(InputRun, ETriggerEvent::Completed, this, &ADPlayer::StopRunning);
	InputComp->BindAction(InputJump, ETriggerEvent::Triggered, this, &ADPlayer::StartJump);

}

void ADPlayer::Walk(const FInputActionValue& InputValue)
{
	const FVector2D AxisInputValue = InputValue.Get<FVector2D>();

	const FVector CharacterFowardVector = GetActorForwardVector();
	const FVector CharacterRightVector = GetActorRightVector();


	AddMovementInput(CharacterFowardVector, AxisInputValue.Y);
	AddMovementInput(CharacterRightVector, AxisInputValue.X);
}

void ADPlayer::Look(const FInputActionValue& InputValue)
{
	const FVector2D Value = InputValue.Get<FVector2D>();
	

	APlayerController* PlayerController = GetController<APlayerController>();

	FRotator ControllerRotation = PlayerController->GetControlRotation();
	

	float ControllerPitch = ControllerRotation.Pitch;

	float MaxAngleDegrees = 0.0f+CameraPitchLimit;
	float MinAngleDegrees = (360.0f - CameraPitchLimit);


	float NewPitch = FMath::ClampAngle((ControllerPitch+Value.Y), MinAngleDegrees, MaxAngleDegrees);
	NewPitch = FRotator::ClampAxis(NewPitch);
	
	FRotator NewRotation = FRotator(NewPitch, ControllerRotation.Yaw, ControllerRotation.Roll);
	
	PlayerController->SetControlRotation(NewRotation);

	AddControllerYawInput(Value.X);
}

void ADPlayer::StartRunning()
{
	CurrentCharacterSpeed = CharacterRunningSpeed;
	
	ChangeSpeedValue(CurrentCharacterSpeed);
}

void ADPlayer::StartJump()
{
	if (CanJump())
		Jump();
}

void ADPlayer::StopRunning()
{
	CurrentCharacterSpeed = CharacterWalkSpeed;
	ChangeSpeedValue(CurrentCharacterSpeed);
}

void ADPlayer::SavePlayerData()
{
	UGameInstance* GameInstance = GetGameInstance();
	UDGameInstance* MyGameInstance = Cast<UDGameInstance>(GameInstance);
	if(MyGameInstance)
	{

		APlayerController* PlayerController = GetController<APlayerController>();
		
		MyGameInstance->PlayerCurrentPosition = GetActorLocation();
		MyGameInstance->PlayerCurrentRotation =  PlayerController->GetControlRotation();
		MyGameInstance->PlayerCurrentSpeed =  CharacterMovementComp->GetMaxSpeed();
		MyGameInstance->PlayerCurrentVelocity = GetVelocity();
	}
}

void ADPlayer::ChangeSpeedValue(float SpeedValue) const
{
	CharacterMovementComp->MaxWalkSpeed = SpeedValue;
}



