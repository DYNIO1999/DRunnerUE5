#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SavingAndLoadingSystem.generated.h"

UCLASS(Blueprintable)
class DRUNNER_API USavingAndLoadingInfo: public UObject
{
	GENERATED_BODY()
public:
	static const FString DirectoryName;
	static const FString FileName;
	static const FString FileExtension;

	UFUNCTION(BlueprintCallable, Category = "Location of saving and loading file")
	static FString GetFileName() {return  FileName;}

	UFUNCTION(BlueprintCallable, Category = "Location of saving and loading file")
	static FString GetDirectoryName() {return  DirectoryName;}

	UFUNCTION(BlueprintCallable, Category = "Location of saving and loading file")
	static FString GetFileExtension() {return  FileExtension;}
};


USTRUCT(BlueprintType) 
struct FPlayerSavedData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	FVector3f PlayerPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) 
	float NumberOfGatheredCoins;

	FPlayerSavedData()
		: PlayerPosition(-1.0f, -1.0f, -1.0f), NumberOfGatheredCoins(-1.0f)
	{
		
	}

	FPlayerSavedData(const FVector& Position, const float Coins)
		: PlayerPosition(Position), NumberOfGatheredCoins(Coins)
	{
		
	}
};

UCLASS()
class DRUNNER_API USavingAndLoadingSystem : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
 
	UFUNCTION(BlueprintCallable, Category="Saving And Loading System")
	static void SavePlayerInfo(const FString& DirectoryName, const FString& FileName, const FPlayerSavedData& PlayerData);

	UFUNCTION(BlueprintCallable, Category="Saving And Loading System")
	static FPlayerSavedData LoadPlayerInfo(const FString& DirectoryName, const FString& FileName);
};