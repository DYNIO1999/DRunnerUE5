#include "DVirtuSphereControllerBasedCode.h"
#include "DRunnerLog.h"

void ADVirtuSphereControllerBasedCode::BeginPlay(){
	Super::BeginPlay();

	DGameInstance = Cast<UDGameInstance>(GetGameInstance());
	IsMotorPowerEnabled = false;
	IsUsingUpAndDowMotor = false;
	IsOnRopeBridge = false;

	Connect();
}
    
void ADVirtuSphereControllerBasedCode::EndPlay(const EEndPlayReason::Type EndPlayReason){
	Super::EndPlay(EndPlayReason);
	SetMotorPower(false);
	Disconnect();
}

void ADVirtuSphereControllerBasedCode::OnConnected_Implementation(){
	Super::OnConnected_Implementation();
	RequestSpherePoseUpdates();
	RequestMotorStateUpdates();
	
}
void ADVirtuSphereControllerBasedCode::OnDisconnected_Implementation(){
	
}
void ADVirtuSphereControllerBasedCode::OnSpherePose_Implementation(FSpherePoseEvent event){
	CurrentPoseEvent =  event;
	//UE_LOG(LogTemp, Error, TEXT("VELOCITY %f"), CurrentPoseEvent.velocity);
}

void ADVirtuSphereControllerBasedCode::OnControllerState_Implementation(FControllerStateEvent event){

}
void ADVirtuSphereControllerBasedCode::OnMotorState_Implementation(FMotorStateEvent event)
{
	if (DGameInstance)
	{
		auto& MotorStateEvents = DGameInstance->SavedMotorStatesEvents;
		const int64 CurrentTimeStamp = event.timestamp;
		if(MotorStateEvents.Contains(CurrentTimeStamp))
		{
			auto& Value = MotorStateEvents[CurrentTimeStamp];
			Value.Add(event);
		}else
		{
			MotorStateEvents.Add(CurrentTimeStamp, {event});	
		}
	}
}


void ADVirtuSphereControllerBasedCode::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	WindDirection = DGameInstance->CurrentWindDirection;
	
	if( (DGameInstance->CurrentPlatformType ==  EGamePlatformType::Ascending) && CanAscend)
	{
		GetWorld()->GetTimerManager().SetTimer(AscendDelay, this, &ADVirtuSphereControllerBasedCode::PerformAscending, 1.0f, true);

		SetMotorPower(true);
		PerformAscending();
		
		CanAscend = false;
	}
	
	if((DGameInstance->CurrentPlatformType !=  EGamePlatformType::Ascending) && !CanAscend){
		CanAscend = true;
		if(GetWorld()->GetTimerManager().IsTimerActive(AscendDelay))
		{
			GetWorld()->GetTimerManager().ClearTimer(AscendDelay);
		}
		SetMotorPower(false);
	}


	
	if( (DGameInstance->CurrentPlatformType ==  EGamePlatformType::Descending) && CanDescend)
	{
		GetWorld()->GetTimerManager().SetTimer(DescendDelay, this, &ADVirtuSphereControllerBasedCode::PerformDescending, 1.0f, true);
		
		SetMotorPower(true);

		PerformDescending();
		
		CanDescend = false;
	}

	if((DGameInstance->CurrentPlatformType !=  EGamePlatformType::Descending) && !CanDescend){
		CanDescend = true;
		if(GetWorld()->GetTimerManager().IsTimerActive(DescendDelay))
		{
			GetWorld()->GetTimerManager().ClearTimer(DescendDelay);
		}
		SetMotorPower(false);
	}

	
	if(DGameInstance->CurrentPlatformType == EGamePlatformType::RopeBridgePlatform && !IsOnRopeBridge)
	{
		GetWorld()->GetTimerManager().SetTimer(WindSwingTimer, this, &ADVirtuSphereControllerBasedCode::PerformSwing, SwingCooldown, true);
		SetMotorPower(true);

		IsOnRopeBridge = true;
		
		PerformSwing();
		
		UE_LOG(DRUNNER, Error, TEXT("SET EVENT"));
	}

	if((DGameInstance->CurrentPlatformType !=  EGamePlatformType::RopeBridgePlatform) && IsOnRopeBridge){
		if(GetWorld()->GetTimerManager().IsTimerActive(WindSwingTimer))
		{
			GetWorld()->GetTimerManager().ClearTimer(WindSwingTimer);
		}

		//Is it necessary??
		const float VelocityAsScalar = CurrentPoseEvent.velocity;
		SetSpherePose(VelocityAsScalar, 0.0f);
		//?

		
		SetMotorPower(false);

		IsOnRopeBridge = false;
		
		
		UE_LOG(DRUNNER, Error, TEXT("UNSET EVENT"));
	}
}

void ADVirtuSphereControllerBasedCode::PerformAscending()
{
	const float VelocityAsScalar = CurrentPoseEvent.velocity;
	const float Direction = CurrentPoseEvent.direction;
	float Result = FMath::Max(VelocityAsScalar - 0.1f, 1.0);
	SetSpherePose(Result, Direction);	
}

void ADVirtuSphereControllerBasedCode::PerformDescending()
{
	const float VelocityAsScalar = CurrentPoseEvent.velocity;
	const float Direction = CurrentPoseEvent.direction;
	// 6 m/s
	float Result = FMath::Min(VelocityAsScalar + 0.5f, 6.0);
	SetSpherePose(Result, Direction);	
}

void ADVirtuSphereControllerBasedCode::PerformSwing()
{
	const float VelocityAsScalar = CurrentPoseEvent.velocity;
	float Result = FMath::Min(VelocityAsScalar + 0.5f, 2.0);

	SetSpherePose(Result, 15.0f*WindDirection.X);
}