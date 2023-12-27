// Fill out your copyright notice in the Description page of Project Settings.


#include "DMainGameModeBase.h"
#include "TestFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "DGameInstance.h"
#include "DCoin.h"
#include "DStandardPlatform.h"

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
		
		//UE_LOG(LogTemp, Warning, TEXT("Witdh %d"), MyGameInstance->ImageLevelInfo.ImageWidthSize);
		//UE_LOG(LogTemp, Warning, TEXT("Height %d"), MyGameInstance->ImageLevelInfo.ImageHeightSize);

		const int ImageWidth = MyGameInstance->ImageLevelInfo.ImageWidthSize;
		const int ImageHeight = MyGameInstance->ImageLevelInfo.ImageHeightSize;
		const int BytesPerPixel = MyGameInstance->ImageLevelInfo.PixelSizeInBytes;

		const auto& ImageRawData = MyGameInstance->ImageLevelInfo.ImageData;
		int PixelCount = 0;
		
		float PlatformPosX = 0;
		float PlatformPosY = 0;
		float PlatformPosZ = 0;
		
		int count =0;
		for (size_t i=0;i<ImageRawData.Num();i++)
		{
			
			
			if(((i+1) % BytesPerPixel) ==0)
			{
				bool IsValid = true;
				
				TArray<int> Pixel;
				//UE_LOG(LogTemp,Error, TEXT("J %d"), i-BytesPerPixel);	
				for(int j=i-(BytesPerPixel-1);j<i;j++)
				{
					
					Pixel.Push(ImageRawData[j]);
						
				}
				for(size_t k=0;k<BytesPerPixel-1;k++)
				{
					if (Pixel[k] != 255)
					{
						IsValid = false;
					}
				}

				if (IsValid)
				{
					FVector PlatformVectorPos= FVector(PlatformPosX, PlatformPosY, PlatformPosZ);
			
					if (GetWorld())
					{
						FActorSpawnParameters SpawnParams;
						SpawnParams.Owner = this;
					
						FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
			
						// Spawn the actor
						AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, PlatformVectorPos, SpawnRotation, SpawnParams);
			
						UE_LOG(LogTemp,Error, TEXT("Spawned Actor %d"), PixelCount);
						//UE_LOG(LogTemp, Warning, TEXT("Height %d"), MyGameInstance->ImageLevelInfo.ImageHeightSize);
						// Additional code to interact with the spawned actor
					}
					PlatformPosX+=1050;
				}

				count++;
			}
			
			// if (((i % BytesPerPixel) == 0) || i !=0)
			// {
			// 	PixelCount++;
			// 	
			// 	
			// 	
			//
			// 	PlatformPosX+=20;
			// 	if (PixelCount > ImageWidth)
			// 	{
			// 		PlatformPosY+=20;
			// 		PlatformPosX=0;
			// 	}
			//
			// 	if (IsValid)
			// 	{
			// 		FVector PlatformVectorPos= FVector(PlatformPosX, PlatformPosY, PlatformPosZ);
			//
			// 		if (GetWorld())
			// 		{
			// 			FActorSpawnParameters SpawnParams;
			// 			SpawnParams.Owner = this;
			// 		
			// 			FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
			//
			// 			// Spawn the actor
			// 			AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, PlatformVectorPos, SpawnRotation, SpawnParams);
			//
			// 			UE_LOG(LogTemp,Error, TEXT("Spawned Actor %d"), PixelCount);
			// 			//UE_LOG(LogTemp, Warning, TEXT("Height %d"), MyGameInstance->ImageLevelInfo.ImageHeightSize);
			// 			// Additional code to interact with the spawned actor
			// 		}
			// 	}
			// 	
			
		}
		UE_LOG(LogTemp,Error, TEXT("Pixel Count %d"), count);
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

}
 

void ADMainGameModeBase::CoinCollected()
{
	CurrentGatheredCoins++;
	UE_LOG(LogTemp, Warning, TEXT("Coin Gathered %d"), CurrentGatheredCoins);
}
