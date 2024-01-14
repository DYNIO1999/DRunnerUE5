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

	UE_LOG(LogTemp, Warning, TEXT("FormattedFileContent:%s"), *PathToFile);
	UE_LOG(LogTemp, Warning, TEXT("FormattedFileContent:%s"), *FileContent);
	bool Result = FFileHelper::SaveStringToFile(FileContent, *PathToFile,FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

FString UTestFunctions::PreProcessLogData(
	const FString& CurrentTime,
	const int PlatformType,
	const int PlatformDirection,
	const int PlatformMovementType,
	const float PlayerSpeed,
	const FVector& PlayerPosition,
	const FRotator& PlayerRotation,
	const FMotorStateEvent& MotorState)
{
	FString RowToSave = FString::Printf(TEXT("%s,%d,%d,%d,%f,%f,%f,%f,%f,%f,%f,%lld,%d,%d,%d,%d,%f,%f,%f\n"), *CurrentTime,
		PlatformType,
		PlatformDirection,
		PlatformMovementType,
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
		MotorState.motorCurrent);

	return RowToSave;
}
