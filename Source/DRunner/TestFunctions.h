// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TestFunctions.generated.h"

/**
 * 
 */
UCLASS()
class DRUNNER_API UTestFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, Category="Test")
	static void DrawTestText();

	UFUNCTION(BlueprintCallable, Category="TestReadPNG")
	static TArray<int> ReadImage(const FString& PathToImage);
	
};
