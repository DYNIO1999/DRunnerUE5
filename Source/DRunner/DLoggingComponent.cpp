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
	const double Now = GetWorld()->GetTimeSeconds();
	
	UDGameInstance* DGameInstance = Cast<UDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if(DGameInstance)
	{
		auto& SavedMotorStates = DGameInstance->SavedMotorStatesEvents;
		if (SavedMotorStates.Num() >= 10)
		{
			TArray<int64> Keys;
			SavedMotorStates.GetKeys(Keys);
			Keys.Sort();
			
			for(const auto Key: Keys)
			{
				
				for(int i =0; i<SavedMotorStates[Key].Num();i++)
				{
					const FString ContentToBeSaved =
						UTestFunctions::PreProcessLogData(
						Now,
						CurrentPlatformType,
						CurrentPlatformDirection,
						CurrentPlatformMovementType,
						DGameInstance->PlayerCurrentSpeed,
						DGameInstance->PlayerCurrentVelocity,
						DGameInstance->PlayerCurrentPosition,
						DGameInstance->PlayerCurrentRotation,
						SavedMotorStates[Key][i],
						static_cast<int>(DGameInstance->CurrentPlayerLeg));
					
					UTestFunctions::SaveContentToFile(FString("LoggedData"), ContentToBeSaved);	
				}
			}
			SavedMotorStates.Reset();
		}
	}
}

