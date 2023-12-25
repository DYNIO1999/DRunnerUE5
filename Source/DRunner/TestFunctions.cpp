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

TArray<int> UTestFunctions::ReadImage(const FString& ImageName)
{
	//figure out path
	const FString ProjectDirectory = FPaths::ProjectDir();
	const  FString ImageDirectoryName{"LevelData"};

	const FString PathToImage = ProjectDirectory+TEXT("/")+ImageDirectoryName+TEXT("/")+ImageName;


	// Load the image wrapper module
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>("ImageWrapper");

	// Create a PNG image wrapper
	 TSharedPtr<IImageWrapper> ImageWrap = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

	// Load the PNG file
	TArray<uint8> FileData;
	if (FFileHelper::LoadFileToArray(FileData, *PathToImage))
	{
		// Decompress the PNG file data
		if (ImageWrap->SetCompressed(FileData.GetData(), FileData.Num()))
		{
			TArray64<uint8> UncompressedData;
            
			// Decompress the image data
			ImageWrap->GetRaw( UncompressedData);

			const size_t NumberOfElements = UncompressedData.GetAllocatedSize()/UncompressedData.GetTypeSize();
			const FString AllocatedSize  = FString::FromInt(NumberOfElements);
			
			if (GEngine)
			{
				constexpr  float MessageTime = 30.0f; 
				const FColor MessageColor = FColor::Red;
				GEngine->AddOnScreenDebugMessage(-1, MessageTime, MessageColor, AllocatedSize);

				for (size_t i =0; i< NumberOfElements ;i++)
				{
					UE_LOG(LogTemp, Warning, TEXT("%d"), UncompressedData[i]);
				}
			}
			
		}
	}
	return  TArray<int>();
}
