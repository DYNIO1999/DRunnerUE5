// Fill out your copyright notice in the Description page of Project Settings.


#include "DMainGameModeBase.h"
#include "TestFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "DGameInstance.h"
#include "DCoin.h"
#include "DRopeBridgePlatform.h"
#include "DStandardPlatform.h"
#include "SavingAndLoadingSystem.h"
#include "DEndPointPlatform.h"
#include "EventManager.h"
#include "IDManager.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Engine/LevelStreaming.h"


void ADMainGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	
	UpdatePlayerAfterLoading = false;
	
	UGameInstance* GameInstance = GetGameInstance();
 
	UDGameInstance* MyGameInstance = Cast<UDGameInstance>(GameInstance);
 
	const FUImageLevelData ImageLevelData = UTestFunctions::ReadImage(ImageFileName);
	
	if (MyGameInstance)
	{
		
		MyGameInstance->ImageLevelInfo = ImageLevelData;
		
	}

	FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	
	MyGameInstance->CurrentMap =  GetMapEnumValue(CurrentLevelName);
	
	if(not UTestFunctions::CheckIfFileExists(USavingAndLoadingInfo::DirectoryName,USavingAndLoadingInfo::FileName, USavingAndLoadingInfo::FileExtension))
	{
		UTestFunctions::DeleteFileIfExists(FString("LoggedInfo"),FString("LoggedData"), FString(".csv"));
		const FString ColumnNamesAsString = UTestFunctions::CreateColumnNames();
		UTestFunctions::SaveContentToFile(FString("LoggedData"), ColumnNamesAsString);
	}
	else
	{
		FString FileName = USavingAndLoadingInfo::GetFileName();
		FString DirectoryName = USavingAndLoadingInfo::GetDirectoryName();
		FString FileExtension = USavingAndLoadingInfo::GetFileExtension();
		if(UTestFunctions::CheckIfFileExists(DirectoryName, FileName, FileExtension))
		{
			const FPlayerSavedData PlayerSavedData = USavingAndLoadingSystem::LoadPlayerInfo(DirectoryName, FileName);
			
			if(not PlayerSavedData.MapName.IsEmpty())
			{
				if  (CurrentLevelName!=*PlayerSavedData.MapName)
				{
					MyGameInstance->CurrentMap =  GetMapEnumValue(PlayerSavedData.MapName);
					UGameplayStatics::OpenLevel(GetWorld(), *PlayerSavedData.MapName);
				}
			}
			UpdatePlayerAfterLoading = true;
		}
	}
	
	UIDManager::ResetID();
}	

void ADMainGameModeBase::StartPlay()
{
	Super::StartPlay();
	
	UGameInstance* GameInstance = GetGameInstance();
	
	UDGameInstance* MyGameInstance = Cast<UDGameInstance>(GameInstance);
	
	float PlayerStartYOffset = 0;
	
	if (MyGameInstance)
	{
		const int ImageWidth = MyGameInstance->ImageLevelInfo.ImageWidthSize;
		const int ImageHeight = MyGameInstance->ImageLevelInfo.ImageHeightSize;
		const int BytesPerPixel = MyGameInstance->ImageLevelInfo.PixelSizeInBytes;
		const auto& ImageRawData = MyGameInstance->ImageLevelInfo.ImageData;

		float PlatformPosX = 0;
		float PlatformPosY = 0;
		float PlatformPosZ = 0;
	
		float PlatformConstantOffset = 1100;
		
		TArray<TArray<FPlatformDefinition>> Map;
		for(size_t i =0;i<ImageHeight;i++)
		{
			Map.Push(TArray<FPlatformDefinition>());
		}

		int I_MapIndex = 0;
		
		int PixelCount = 0;
		for (size_t i=0;i<ImageRawData.Num();i+= BytesPerPixel)
		{	
			if(PixelCount == ImageWidth)
			{
				PixelCount=0;
				I_MapIndex++;
			}
			if (i + 3 < ImageRawData.Num())
			{
				const EGamePlatformType PlatformType = CheckPlatformType(ImageRawData[i]);
				const EGamePlatformDirection PlatformDirection = CheckPlatformDirection(ImageRawData[i+1]);
				const EGamePlatformMovementType PlatformMovement = CheckPlatformMovementType(ImageRawData[i+2]);
				Map[I_MapIndex].Push(FPlatformDefinition(PlatformType,PlatformDirection, PlatformMovement)); 
				PixelCount++;
			}
		}
		
		for(size_t i =0;i<ImageHeight;i++)
		{
			for(size_t j =0;j<ImageWidth;j++)
			{
				EGamePlatformType CurrentPlatformType = Map[i][j].PlatformType;
				EGamePlatformDirection CurrentPlatformDirection = Map[i][j].PlatformDirection;
				EGamePlatformMovementType CurrentPlatformMovementType = Map[i][j].MovementType;
				bool IsAlreadySet = Map[i][j].AlreadySet;
				
				bool IsValid = true;
				if (Map[i][j].PlatformType == EGamePlatformType::None)
				{
					IsValid = false;
				}
				if (IsValid)
				{
					FVector PlatformVectorPos= FVector(PlatformPosX, PlatformPosY, PlatformPosZ);
					
					if (CurrentPlatformMovementType == EGamePlatformMovementType::SpawnPoint)
					{
						PlayerStartYOffset = PlatformPosY;	
					}
					
				

					TSubclassOf<AActor> ActorToSpawn = ChooseActorToSpawn(CurrentPlatformType, CurrentPlatformDirection, CurrentPlatformMovementType);
					
					if (GetWorld())
					{
						FActorSpawnParameters SpawnParams;
						SpawnParams.Owner = this;
					
										
						float angleYaw  = GetAngleBasedOnPlatformDirection(CurrentPlatformType, CurrentPlatformDirection);
						FRotator SpawnRotation = FRotator(0.0f, angleYaw, 0.0f);
										

						if (CurrentPlatformType == EGamePlatformType::RopeBridgePlatform) {
							PlatformVectorPos = PlatformVectorPos + FVector(0.0f, 0.0, 80.0f);
						}
						
						if(!IsAlreadySet)
						{
							AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, PlatformVectorPos, SpawnRotation, SpawnParams);
										
							if (CurrentPlatformType == EGamePlatformType::RopeBridgePlatform) {
								int BridgeSize = 1;

								if (i> 0  && i < ImageHeight && j>0 && j < ImageWidth)
								{
									//UE_LOG(LogTemp, Error, TEXT("TEST"));
									for(int k=1;k<=3;k++)
									{
										if (Map[i][j+k].PlatformType == EGamePlatformType::RopeBridgePlatform)
										{
											Map[i][j+k].AlreadySet = true;
											BridgeSize++;
										}else
										{
											break;
										}
									}
								
									for(int k=1;k<=3;k++)
									{
										if (Map[i+k][j].PlatformType == EGamePlatformType::RopeBridgePlatform)
										{
											Map[i+k][j].AlreadySet = true;
											BridgeSize++;
										}else
										{
											break;
										}
									}
									Map[i][j].AlreadySet = true;
								
								}
								ADRopeBridgePlatform* RopeBridgePlatformPtr = Cast<ADRopeBridgePlatform>(SpawnedActor);
								RopeBridgePlatformPtr->InitializePlatform(CurrentPlatformType, CurrentPlatformDirection, CurrentPlatformMovementType);

								//UE_LOG(LogTemp, Error, TEXT("BRIDGE SIZE %d"), BridgeSize);
								RopeBridgePlatformPtr->CreateBridge(RopeBridgePlatformPtr->NumberOfPlanks*BridgeSize+1);
							}
							else {
								if (CurrentPlatformType == EGamePlatformType::EndPointPlatform){
									ADEndPointPlatform* EndPointPlatform = Cast<ADEndPointPlatform>(SpawnedActor);
									EndPointPlatform->InitializePlatform(CurrentPlatformType, CurrentPlatformDirection, CurrentPlatformMovementType);
								}else
								{
									ADStandardPlatform* StandardPlatform = Cast<ADStandardPlatform>(SpawnedActor);
									StandardPlatform->InitializePlatform(CurrentPlatformType, CurrentPlatformDirection, CurrentPlatformMovementType);
								}
							}
						}
					}
					
				}
				PlatformPosX+=PlatformConstantOffset;	
				
			}
			PlatformPosX = 0;
			PlatformPosY+=PlatformConstantOffset;
		}
	}
	
	TArray<AActor*> FoundCoins;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADCoin::StaticClass(), FoundCoins);

	MaxCoinsOnLevel= FoundCoins.Num();
	MyGameInstance->MaxPointsToGather = MaxCoinsOnLevel;

	for(int i = 0; i < FoundCoins.Num(); i++)
	{
		ADCoin* TempCoin = Cast<ADCoin>(FoundCoins[i]);
		TempCoin->OnEventGathered.AddDynamic(this, &ADMainGameModeBase::CoinCollected);
	}
	
	SetPlayerStartLocation(PlayerStartYOffset);

	UEventManager::PerformSavingPlayerInfoDelegate.AddDynamic(this, &ADMainGameModeBase::HandleSavingPlayerInfo);
	UEventManager::PerformLoadingPlayerInfoDelegate.AddDynamic(this, &ADMainGameModeBase::HandleLoadingPlayerInfo);
	
	if(UpdatePlayerAfterLoading)
	{
		FString FileName = USavingAndLoadingInfo::GetFileName();
		FString DirectoryName = USavingAndLoadingInfo::GetDirectoryName();
		FString FileExtension = USavingAndLoadingInfo::GetFileExtension();
		if(UTestFunctions::CheckIfFileExists(DirectoryName, FileName, FileExtension))
		{
			const FPlayerSavedData PlayerSavedData = USavingAndLoadingSystem::LoadPlayerInfo(DirectoryName, FileName);
			UpdatedCollectedAndPosition(PlayerSavedData.PlayerPosition, PlayerSavedData.NumberOfGatheredCoins);
		}
	}

	
	MyGameInstance->TrackingTimeOfHMD = {0.0};
	MyGameInstance->GamePlayTimePerMap = {0.0};
	
}


TSubclassOf<AActor> ADMainGameModeBase::ChooseActorToSpawn(const EGamePlatformType PlatformTypePar,
	const EGamePlatformDirection PlatformDirectionPar, const EGamePlatformMovementType MovementTypePar)
{
	if (PlatformTypePar == EGamePlatformType::Standard)
	{
		return ForwardStandardPlatform;
	}

	if(PlatformTypePar == EGamePlatformType::LeftPlatform)
	{
		return LeftStandardPlatformActor;
	}

	if(PlatformTypePar == EGamePlatformType::RightPlatform)
	{
		return RightStandardPlatform;
	}

	if(PlatformTypePar == EGamePlatformType::Ascending)
	{
		return AscendingPlatform;
	}

	if(PlatformTypePar == EGamePlatformType::Descending)
	{
		return DescendingPlatform;
	}

	if (PlatformTypePar == EGamePlatformType::RopeBridgePlatform)
	{
		return RopeBridgePlatformRef;
	}

	if (PlatformTypePar == EGamePlatformType::RopeBridgePlatform)
	{
		return RopeBridgePlatformRef;
	}

	if (PlatformTypePar == EGamePlatformType::EndPointPlatform)
	{
		return EndPointPlatformRef;
	}
	
	
	return ForwardStandardPlatform;
}

void ADMainGameModeBase::UpdatedCollectedAndPosition(FVector PlayerPos, float NumberOfCoinsGathered)
{
	UWorld* World = GetWorld();
	if (World)
	{
		UGameInstance* GameInstance = GetGameInstance();

		UDGameInstance* MyGameInstance = Cast<UDGameInstance>(GameInstance);
		
		PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(World, 0));
		APawn* PlayerPawn  = PlayerController->GetPawn();;

		PlayerPawn->SetActorLocation(PlayerPos);
		CurrentGatheredCoins = NumberOfCoinsGathered;
		MyGameInstance-> CurrentGatheredPoints = CurrentGatheredCoins;

		OnEventLoadedUpdateUIDelegate.Broadcast();
	}
}

void ADMainGameModeBase::CoinCollected(float MultiplayerPerPoint)
{
	CurrentGatheredCoins += MultiplayerPerPoint*1.0f;
	//UE_LOG(LogTemp, Warning, TEXT("Coin Gathered %d"), CurrentGatheredCoins);
	UGameInstance* GameInstance = GetGameInstance();

	UDGameInstance* MyGameInstance = Cast<UDGameInstance>(GameInstance);

	MyGameInstance->CurrentGatheredPoints = CurrentGatheredCoins;
	
}


void ADMainGameModeBase::SetPlayerStartLocation(float PlayerStartOffsetY)
{

	UWorld* World = GetWorld();
	if (World)
	{
		PlayerController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(World, 0));
	}
	
	if(PlayerController)
	{
		APawn* PlayerPawn  = PlayerController->GetPawn();

		FVector ActorLocation = PlayerPawn->GetActorLocation();
		ActorLocation+=FVector(0,PlayerStartOffsetY, 0.0f);
		PlayerPawn->SetActorLocation(ActorLocation);
	}
}

void ADMainGameModeBase::HandleLoadingPlayerInfo()
{
	FString FileName = USavingAndLoadingInfo::GetFileName();
	FString DirectoryName = USavingAndLoadingInfo::GetDirectoryName();
	FString FileExtension = USavingAndLoadingInfo::GetFileExtension();
	if(UTestFunctions::CheckIfFileExists(DirectoryName, FileName, FileExtension))
	{
		const FPlayerSavedData PlayerSavedData = USavingAndLoadingSystem::LoadPlayerInfo(DirectoryName, FileName);

		if(not PlayerSavedData.MapName.IsEmpty())
		{
			FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());

			if  (CurrentLevelName!=*PlayerSavedData.MapName)
			{
				UGameInstance* GameInstance = GetGameInstance();
				UDGameInstance* MyGameInstance = Cast<UDGameInstance>(GameInstance);
				
				MyGameInstance->CurrentMap =  GetMapEnumValue(CurrentLevelName);
				UGameplayStatics::OpenLevel(GetWorld(), *PlayerSavedData.MapName);
			}
		}
		UpdatedCollectedAndPosition(PlayerSavedData.PlayerPosition, PlayerSavedData.NumberOfGatheredCoins);
	}
}

void ADMainGameModeBase::HandleSavingPlayerInfo()
{
	FString DirectoryName = USavingAndLoadingInfo::GetDirectoryName();
	FString FileName = USavingAndLoadingInfo::GetFileName();

	UGameInstance* GameInstance = GetGameInstance();
	UDGameInstance* MyGameInstance = Cast<UDGameInstance>(GameInstance);

	FString MapName = GetMapName(MyGameInstance->CurrentMap);
	FPlayerSavedData PlayInfo(MyGameInstance->PlayerCurrentPosition, MyGameInstance->CurrentGatheredPoints, MapName);
	
	USavingAndLoadingSystem::SavePlayerInfo(DirectoryName, FileName, PlayInfo);
}
