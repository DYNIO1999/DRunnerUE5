// Fill out your copyright notice in the Description page of Project Settings.


#include "DMainGameModeBase.h"
#include "TestFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "DGameInstance.h"
#include "DCoin.h"

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

	TArray<AActor*> FoundCoins;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADCoin::StaticClass(), FoundCoins);
	MaxCoinsOnLevel= FoundCoins.Num();
	UE_LOG(LogTemp, Warning, TEXT("Max Coins on level %d"), MaxCoinsOnLevel);
	
	
	for(int i = 0; i < FoundCoins.Num(); i++)
	{
		ADCoin* TempCoin = Cast<ADCoin>(FoundCoins[i]);
		TempCoin->OnEventGathered.AddDynamic(this, &ADMainGameModeBase::CoinCollected);
	}
	
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

void ADMainGameModeBase::StartPlay()
{
	Super::StartPlay();
}
 

void ADMainGameModeBase::CoinCollected()
{
	CurrentGatheredCoins++;
	UE_LOG(LogTemp, Warning, TEXT("Coin Gathered %d"), CurrentGatheredCoins);
}
