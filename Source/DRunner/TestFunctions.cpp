// Fill out your copyright notice in the Description page of Project Settings.


#include "TestFunctions.h"
#include "Misc/Paths.h"
#include "Engine/Texture2D.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Engine/Texture2D.h"
#include "Modules/ModuleManager.h"


void UTestFunctions::DrawTestText()
{
	printf("Hello World");
	fflush(stdout);

	const FString ProjectDirectory = FPaths::ProjectDir();
	
	if (GEngine)
	{
		constexpr  float MessageTime = 1.0f; 
		const FColor MessageColor = FColor::Green;
		GEngine->AddOnScreenDebugMessage(-1, MessageTime, MessageColor, ProjectDirectory);
	}
	
}

FUImageLevelData UTestFunctions::ReadImage(const FString& ImageName)
{
	const FString ProjectDirectory = FPaths::ProjectDir();
	const  FString ImageDirectoryName{"LevelData"};

	const FString PathToImage = FPaths::ConvertRelativePathToFull(ProjectDirectory+ImageDirectoryName+TEXT("/")+ImageName);
	
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>("ImageWrapper");
	
	TSharedPtr<IImageWrapper> ImageWrap = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

	int ImageWidth{};
	int ImageHeight{};
	
	TArray<int> ImageDataToBeCopied;
	
	
	TArray<uint8> FileData;
	if (FFileHelper::LoadFileToArray(FileData, *PathToImage))
	{
		
		
		if (ImageWrap->SetCompressed(FileData.GetData(), FileData.Num()))
		{
			TArray64<uint8> UncompressedData;
            
			ImageWrap->GetRaw( ERGBFormat::RGBA,ImageWrap->GetBitDepth(), UncompressedData);

			ImageWidth = ImageWrap->GetWidth();
			ImageHeight = ImageWrap->GetHeight();
			
			for(int i =0;i<UncompressedData.Num();i++)
			{
				ImageDataToBeCopied.Push(UncompressedData[i]);
				
			}
		}
	}
	return  FUImageLevelData(ImageDataToBeCopied, ImageWidth, ImageHeight, 4);
}

void UTestFunctions::SaveContentToFile(const FString& FileName, const FString& FileContent)
{
	const FString ProjectDirectory = FPaths::ProjectDir();
	const  FString LoggingDirName{"LoggedInfo"};
	const FString PathToFile= FPaths::ConvertRelativePathToFull(ProjectDirectory+LoggingDirName+TEXT("/")+(FileName+TEXT(".csv")));
	FFileHelper::SaveStringToFile(FileContent, *PathToFile,FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

FString UTestFunctions::PreProcessLogData(
	const float CurrentTime,
	const int PlatformType,
	const int PlatformDirection,
	const int PlatformMovementType,
	const float PlayerSpeed,
	const FVector& PlayerVelocity,
	const FVector& PlayerPosition,
	const FRotator& PlayerRotation,
	const FMotorStateEvent& MotorState,
	const FRotator& HMDRotation,
	const int GatheredFromDirection,
	const int CoinID,
	const float TrackingTime,
	const float WholeTime)
{
	FString RowToSave = FString::Printf(TEXT("%f,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%lld,%d,%d,%d,%d,%f,%f,%f,%f,%f,%f,%d,%d,%f,%f\n"),
		CurrentTime,
		PlatformType,
		PlatformDirection,
		PlatformMovementType,
		PlayerVelocity.X,
		PlayerVelocity.Y,
		PlayerVelocity.Z,
		PlayerPosition.X,
		PlayerPosition.Y,
		PlayerPosition.Z,
		PlayerRotation.Roll,
		PlayerRotation.Pitch,
		PlayerRotation.Yaw,
		PlayerSpeed,
		MotorState.timestamp,
		MotorState.controllerId,
		MotorState.motorFlags,
		MotorState.hallPosition,
		MotorState.encoderPosition,
		MotorState.motorVelocity,
		MotorState.motorVoltage,
		MotorState.motorCurrent,
		HMDRotation.Roll,
		HMDRotation.Pitch,
		HMDRotation.Yaw,
		GatheredFromDirection,
		CoinID,
		TrackingTime,
		WholeTime);

	return RowToSave;
}

FString UTestFunctions::CreateColumnNames()
{
	FString RowToSave = FString::Printf(TEXT("CurrentTime,PlatformType,PlatformDirection,PlatformMovementType,PlayerVelocity.x,PlayerVelocity.y,PlayerVelocity.z,PlayerPosition.x,PlayerPosition.y,PlayerPosition.z,PlayerRotation.Pitch,PlayerRotation.Roll,PlayerRotation.Yaw,PlayerCurrentSpeed,UnixTimeStamp [us],ControllerId,MotorFlags,HallPosition,EncoderPosition,MotorVelocity,MotorVoltage,MotorCurrent,HMDRotation.Pitch,HMDRotation.Roll,HMDRotation.Yaw,PointGatheredFromDirection,GatheredPointID,TrackingTime,WholeTime\n"));
	return RowToSave;
}

bool UTestFunctions::CheckIfFileExists(const FString& DirectoryName, const FString& FileName, const FString& Extension)
{
	const FString ProjectDirectory = FPaths::ProjectDir();
	const FString PathToFile= FPaths::ConvertRelativePathToFull(ProjectDirectory+DirectoryName+TEXT("/")+(FileName+Extension));

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.FileExists(*PathToFile))
	{
		return true;
	}
	return false;	
}


void UTestFunctions::DeleteFileIfExists(const FString& DirectoryName, const FString& FileName, const FString& Extension)
{
	const FString ProjectDirectory = FPaths::ProjectDir();
	const FString PathToFile= FPaths::ConvertRelativePathToFull(ProjectDirectory+DirectoryName+TEXT("/")+(FileName+Extension));

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	if (PlatformFile.FileExists(*PathToFile))
	{
		if(PlatformFile.DeleteFile(*PathToFile))
			UE_LOG(LogTemp, Error, TEXT("File Deleted:%s"), *PathToFile);
	}
}
