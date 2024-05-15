// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/FileHelper.h"
#include "VirtuSphereClient/Public/VirtuSphereClientStructs.h"
#include "TestFunctions.generated.h"


USTRUCT(BlueprintType)
struct FUImageLevelData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FUImageLevelData")
	TArray<int> ImageData;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FUImageLevelData")
	int ImageWidthSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FUImageLevelData")
	int ImageHeightSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FUImageLevelData")
	int PixelSizeInBytes;
	

	FUImageLevelData()
		: ImageData{}, ImageWidthSize(0), ImageHeightSize(0), PixelSizeInBytes(0)
	{
		
	}
	
	FUImageLevelData(const TArray<int>& ImageDataPar, const int ImageWidthSizePar, const int ImageHeightSizePar, const int PixelSizeInBytesPar)
		: ImageData{ImageDataPar}, ImageWidthSize(ImageWidthSizePar), ImageHeightSize(ImageHeightSizePar), PixelSizeInBytes(PixelSizeInBytesPar)
	{
		
	}
};
UCLASS()
class DRUNNER_API UTestFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="Test")
	static void DrawTestText();

	UFUNCTION(BlueprintCallable, Category="TestReadPNG")
	static FUImageLevelData ReadImage(const FString& PathToImage);

	UFUNCTION(BlueprintCallable, Category="Saving Data to File")
	static void SaveContentToFile(const FString& FileName, const FString& FileContent);

	UFUNCTION(BlueprintCallable, Category="Saving Data to File")
	static FString PreProcessLogData(
	const float CurrentTime,
	const int PlatformType,
	const int PlatformDirection,
	const int PlatformMovementType,
	const float PlayerSpeed,
	const FVector& PlayerVelocity,
	const FVector& PlayerPosition,
	const FRotator& PlayerRotation,
	const FMotorStateEvent& MotorStates,
	const int CurrentLeg,
	const int GatheredFromDirection,
	const int CoinID);

	UFUNCTION(BlueprintCallable, Category="Saving Data to File")
	static FString CreateColumnNames();

	UFUNCTION(BlueprintCallable, Category="Saving Data to File")
	static bool CheckIfFileExists(const FString& DirectoryName, const FString& FileName, const FString& Extension);
	
	UFUNCTION(BlueprintCallable, Category="Saving Data to File")
    	static void DeleteFileIfExists(const FString& DirectoryName, const FString& FileName, const FString& Extension);
};
