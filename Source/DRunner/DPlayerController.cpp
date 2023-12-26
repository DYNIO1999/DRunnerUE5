// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"

void ADPlayerController::SetPawn(APawn* InPawn) {
	Super::SetPawn(InPawn);
}

void ADPlayerController::BeginPlayingState()
{
	BlueprintBeginPlayingState();
}
