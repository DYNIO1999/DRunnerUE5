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
		
		const int ImageWidth = MyGameInstance->ImageLevelInfo.ImageWidthSize;
		const int BytesPerPixel = MyGameInstance->ImageLevelInfo.PixelSizeInBytes;

		const auto& ImageRawData = MyGameInstance->ImageLevelInfo.ImageData;
		
		int PixelCount = 0;
		
		float PlatformPosX = 0;
		float PlatformPosY = 0;
		float PlatformPosZ = 0;

		float PlatformConstantOffset = 1100;

		for (size_t i=0;i<ImageRawData.Num();i++)
		{
			
			if(((i+1) % BytesPerPixel) ==0)
			{
				
				
				bool IsValid = true;
				
				if(PixelCount==ImageWidth)
				{
					PlatformPosX=0;
					PlatformPosY+=PlatformConstantOffset;
					PixelCount= 0;
				}
				
				TArray<int> Pixel;
				for(int j=i-(BytesPerPixel-1);j<i;j++)
				{
					
					Pixel.Push(ImageRawData[j]);
						
				}

				EGamePlatformType PlatformType = CheckPlatformType(Pixel[0]);
				if (PlatformType == EGamePlatformType::None)
				{
					IsValid = false;
				}
				
				if (IsValid)
				{
					FVector PlatformVectorPos= FVector(PlatformPosX, PlatformPosY, PlatformPosZ);
					
					if (GetWorld())
					{
						FActorSpawnParameters SpawnParams;
						SpawnParams.Owner = this;
					
						FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);
						
						AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ForwardStandardPlatform, PlatformVectorPos, SpawnRotation, SpawnParams);
				
						ADStandardPlatform* StandardPlatform = Cast<ADStandardPlatform>(SpawnedActor);
						

						//StandardPlatform->InitializePlatform(PlatformType,);
						
						
					}
				}
				
				PlatformPosX+=PlatformConstantOffset;
				PixelCount++;
			}
		}
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


TSubclassOf<AActor> ADMainGameModeBase::ChooseActorToSpawn(const EGamePlatformType PlatformTypePar,
	const EGamePlatformDirection PlatformDirectionPar, const EGamePlatformMovementType MovementTypePar)
{
	if (PlatformTypePar == EGamePlatformType::Standard && PlatformDirectionPar == EGamePlatformDirection::Forward)
	{
		return ForwardStandardPlatform;
	}

	if(PlatformTypePar == EGamePlatformType::Standard && PlatformDirectionPar == EGamePlatformDirection::Left)
	{
		return LeftStandardPlatformActor;
	}

	if(PlatformTypePar == EGamePlatformType::Standard && PlatformDirectionPar == EGamePlatformDirection::Right)
	{
		return RightStandardPlatform;
	}
	
	return ForwardStandardPlatform;
}

void ADMainGameModeBase::CoinCollected()
{
	CurrentGatheredCoins++;
	UE_LOG(LogTemp, Warning, TEXT("Coin Gathered %d"), CurrentGatheredCoins);
}
