#include "DLoggingComponent.h"
#include "DGameInstance.h"
#include "TestFunctions.h"
#include "Kismet/GameplayStatics.h"

UDLoggingComponent::UDLoggingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UDLoggingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDLoggingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UDLoggingComponent::SaveLoggedData(
	int CurrentPlatformType,
	int CurrentPlatformDirection,
	int CurrentPlatformMovementType)
{
	const FDateTime Now = FDateTime::Now();
	const FString CurrentTimeAsString = Now.ToString(TEXT("%S-%s"));
	
	UDGameInstance* DGameInstance = Cast<UDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if(DGameInstance)
	{
		if(DGameInstance->CurrentMotorStateEvent.Num() >=4)
		{
			for(int i =0; i< 4; i++)
			{
				const FString ContentToBeSaved =
					UTestFunctions::PreProcessLogData(
						CurrentTimeAsString,
						CurrentPlatformType,
						CurrentPlatformDirection,
						CurrentPlatformMovementType,
						DGameInstance->PlayerCurrentSpeed,
						DGameInstance->PlayerCurrentVelocity,
						DGameInstance->PlayerCurrentPosition,
						DGameInstance->PlayerCurrentRotation,
						DGameInstance->CurrentMotorStateEvent[i]);	
				UTestFunctions::SaveContentToFile(FString("LoggedData"), ContentToBeSaved);		
			}
		}
	}
}

