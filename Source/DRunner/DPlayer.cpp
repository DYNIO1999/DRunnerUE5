#include "DPlayer.h"

#include "DCoin.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/AudioComponent.h"
#include "DGameInstance.h"
#include "DrawDebugHelpers.h"
#include "EventManager.h"


ADPlayer::ADPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");

	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
	
	PlayerRightLegAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("PlayerRightLegAudio"));
	PlayerRightLegAudio->SetupAttachment(RootComponent);

	PlayerRightLegAudio->bAutoActivate = false;

	PlayerLeftLegAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("PlayerLeftLegAudio"));
	PlayerLeftLegAudio->SetupAttachment(RootComponent);

	PlayerLeftLegAudio->bAutoActivate = false;

	PlayerPickedUpAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("PlayerPickedUpAudio"));
	PlayerPickedUpAudio->SetupAttachment(RootComponent);

	PlayerPickedUpAudio->bAutoActivate = false;
}

void ADPlayer::BeginPlay()
{
	
	Super::BeginPlay();

	CharacterMovementComp = GetCharacterMovement<UCharacterMovementComponent>();
	
	CurrentCharacterSpeed = CharacterWalkSpeed;
	CharacterMovementComp->MaxWalkSpeed = CurrentCharacterSpeed;
	
	UGameInstance* GameInstance = GetGameInstance();
	DGameInstanceRef = Cast<UDGameInstance>(GameInstance);
	
	GetWorldTimerManager().SetTimer(PlayerDataSavingTimer, this, &ADPlayer::SavePlayerData, 0.1f, true);
	
	DGameInstanceRef ->ChangeLegCooldown = ChangeLegCooldown;
	PreviousPlatformMovementType = DGameInstanceRef->CurrentPlatformMovementType;
	GetWorldTimerManager().SetTimer(ChangeLegCooldownTimer, this, &ADPlayer::ChangeLeg, ChangeLegCooldown, true);

	UEventManager::PlaySoundGatheredDelegate.AddDynamic(this, &ADPlayer::PlayPickedUpCoinSound);
	UEventManager::LostXRHeadsetTrackingDelegate.AddDynamic(this, &ADPlayer::HandleLostTrackingOnXRHeadset);
	
}

void ADPlayer::PlayerDead()
{
	OnEventPlayerLost.Broadcast();
}

void ADPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PreviousPlatformMovementType != DGameInstanceRef->CurrentPlatformMovementType)
	{
		if (DGameInstanceRef->CurrentPlatformMovementType == EGamePlatformMovementType::Running)
		{
			GetWorld()->GetTimerManager().ClearTimer(ChangeLegCooldownTimer);
			ChangeLegCooldown = RunningLegCooldown;
			DGameInstanceRef->ChangeLegCooldown = ChangeLegCooldown;	
			GetWorldTimerManager().SetTimer(ChangeLegCooldownTimer, this, &ADPlayer::ChangeLeg, ChangeLegCooldown, true);		

			
		}else
		{
			GetWorld()->GetTimerManager().ClearTimer(ChangeLegCooldownTimer);
			ChangeLegCooldown = WalkingLegCooldown;
			DGameInstanceRef->ChangeLegCooldown = ChangeLegCooldown;	
			GetWorldTimerManager().SetTimer(ChangeLegCooldownTimer, this, &ADPlayer::ChangeLeg, ChangeLegCooldown, true);
		}
		PreviousPlatformMovementType = DGameInstanceRef->CurrentPlatformMovementType;
	}
	
	

	// TArray<AActor*> FoundCoins;
	// UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADCoin::StaticClass(), FoundCoins);
	//
	// for(int i = 0; i < FoundCoins.Num(); i++)
	// {
	// 	ADCoin* CoinObjectPtr = Cast<ADCoin>(FoundCoins[i]);
	// 	FVector CoinLocation = CoinObjectPtr->GetActorLocation();
	// }
	// //check for closer platform 
	
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
	
	InputComp->BindAction(InputLoadPlayerInfo, ETriggerEvent::Completed, this, &ADPlayer::PressedLoadPlayerInfo);
	InputComp->BindAction(InputSavePlayerInfo, ETriggerEvent::Completed, this, &ADPlayer::PressedSavePlayerInfo);
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

void ADPlayer::PressedLoadPlayerInfo()
{
	UE_LOG(LogTemp, Error, TEXT("PRESSED LOAD PLAYER INFO"));
	UEventManager::PerformLoadingPlayerInfoDelegate.Broadcast();
}

void ADPlayer::PressedSavePlayerInfo()
{
	UE_LOG(LogTemp, Error, TEXT("PRESSED SAVED PLAYER INFO"));
	UEventManager::PerformSavingPlayerInfoDelegate.Broadcast();
}

void ADPlayer::SavePlayerData()
{
	
	if(DGameInstanceRef)
	{

		APlayerController* PlayerController = GetController<APlayerController>();
		
		DGameInstanceRef->PlayerCurrentPosition = GetActorLocation();
		DGameInstanceRef->PlayerCurrentRotation =  PlayerController->GetControlRotation();
		DGameInstanceRef->PlayerCurrentSpeed =  CharacterMovementComp->GetMaxSpeed();
		DGameInstanceRef->PlayerCurrentVelocity = GetVelocity();
	}
}

void ADPlayer::ChangeLeg()
{
	if(DGameInstanceRef)
	{
		if (DGameInstanceRef->CurrentPlatformMovementType != EGamePlatformMovementType::SpawnPoint)
		{
			if (PlayerCurrentLeg == EGameUsedLeg::Left){

				PlayerRightLegAudio->Play();
				PlayerCurrentLeg = EGameUsedLeg::Right;
			}
			else
			{
				PlayerLeftLegAudio->Play();
				PlayerCurrentLeg =EGameUsedLeg::Left;
			}
			DGameInstanceRef->CurrentPlayerLeg = PlayerCurrentLeg;
		}
	}
}

void ADPlayer::PlayPickedUpCoinSound()
{
	PlayerPickedUpAudio->Play();
}

void ADPlayer::HandleLostTrackingOnXRHeadset(FRotator NewRotation)
{
	
	CameraComp->SetRelativeRotation(NewRotation);
}

void ADPlayer::ChangeSpeedValue(float SpeedValue) const
{
	CharacterMovementComp->MaxWalkSpeed = SpeedValue;
}



