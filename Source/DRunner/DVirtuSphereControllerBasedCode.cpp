// Fill out your copyright notice in the Description page of Project Settings.


#include "DVirtuSphereControllerBasedCode.h"
#include "DGameInstance.h"

void ADVirtuSphereControllerBasedCode::BeginPlay(){
	Super::BeginPlay();
	Connect();
}
    
void ADVirtuSphereControllerBasedCode::EndPlay(const EEndPlayReason::Type EndPlayReason){
	Super::EndPlay(EndPlayReason);
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
	
}

void ADVirtuSphereControllerBasedCode::OnControllerState_Implementation(FControllerStateEvent event){

}
void ADVirtuSphereControllerBasedCode::OnMotorState_Implementation(FMotorStateEvent event)
{
	//UE_LOG(LogTemp, Error, TEXT("TimeStamp %lld"), event.timestamp);

	UGameInstance* GameInstance = GetGameInstance();
	
	UDGameInstance* DRunnerGameInstance = Cast<UDGameInstance>(GameInstance);

	if (DRunnerGameInstance)
	{
		auto& MotorStateEvents = DRunnerGameInstance->SavedMotorStatesEvents;
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
}