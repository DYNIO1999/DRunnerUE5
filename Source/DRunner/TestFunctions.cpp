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

	const FString PathToImage = ProjectDirectory+TEXT("/")+ImageDirectoryName+TEXT("/")+ImageName;
	
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
