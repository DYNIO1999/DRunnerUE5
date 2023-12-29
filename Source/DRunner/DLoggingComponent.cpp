#include "DLoggingComponent.h"
#include "TestFunctions.h"
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

void UDLoggingComponent::SaveLoggedData()
{
	//DATE AND TIME | PLATFORM TYPE | PLATFORM DIRECTION | MOVEMENT TYPE |....
	FDateTime Now = FDateTime::Now();
	FString CurrentTimeAsString = Now.ToString();
	UTestFunctions::SaveContentToFile(FString("LoggedData"), CurrentTimeAsString);
}

