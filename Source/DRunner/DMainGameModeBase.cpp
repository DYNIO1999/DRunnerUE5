// Fill out your copyright notice in the Description page of Project Settings.


#include "DMainGameModeBase.h"
#include "TestFunctions.h"

#include "DGameInstance.h"

void ADMainGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	UGameInstance* GameInstance = GetGameInstance();

	UDGameInstance* MyGameInstance = Cast<UDGameInstance>(GameInstance);

	const FUImageLevelData ImageLevelData = UTestFunctions::ReadImage(ImageFileName);
	
	if (MyGameInstance)
	{
		
		MyGameInstance->ImageLevelInfo = ImageLevelData;
		
	}
}

void ADMainGameModeBase::StartPlay()
{
	Super::StartPlay();


	UGameInstance* GameInstance = GetGameInstance();

	UDGameInstance* MyGameInstance = Cast<UDGameInstance>(GameInstance);

	if (MyGameInstance)
	{
		
		UE_LOG(LogTemp, Warning, TEXT("Witdh %d"), MyGameInstance->ImageLevelInfo.ImageWidthSize);
		UE_LOG(LogTemp, Warning, TEXT("Height %d"), MyGameInstance->ImageLevelInfo.ImageHeightSize);
		const auto& ImageRawData = MyGameInstance->ImageLevelInfo.ImageData;
		for(size_t i=0;i<ImageRawData.Num();i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("%d"), ImageRawData[i]);
		}
	}
}
