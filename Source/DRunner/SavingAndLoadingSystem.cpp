#include "SavingAndLoadingSystem.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonReader.h"
#include "TestFunctions.h"

const FString USavingAndLoadingInfo::DirectoryName  = FString("SavedPlayerInfo");
const FString USavingAndLoadingInfo::FileName = FString("PlayerLocationInfo");
const FString USavingAndLoadingInfo::FileExtension  = FString(".json");

void USavingAndLoadingSystem::SavePlayerInfo(const FString& DirectoryName, const FString& FileName,
	const FPlayerSavedData& PlayerData)
{
	const TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	TArray<TSharedPtr<FJsonValue>> Values;
	Values.Add(MakeShared<FJsonValueNumber>(PlayerData.PlayerPosition.X));
	Values.Add(MakeShared<FJsonValueNumber>(PlayerData.PlayerPosition.Y));
	Values.Add(MakeShared<FJsonValueNumber>(PlayerData.PlayerPosition.Z));

	JsonObject->SetArrayField("PlayerPosition", Values);
	JsonObject->SetNumberField("NumberOfGatheredCoins", PlayerData.NumberOfGatheredCoins);

	if(!PlayerData.MapName.IsEmpty())
		JsonObject->SetStringField("CurrentMap", PlayerData.MapName);

	FString OutputString;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	const FString ProjectDirectory = FPaths::ProjectDir();
	const FString PathToFile= FPaths::ConvertRelativePathToFull(ProjectDirectory+DirectoryName+TEXT("/")+(FileName+TEXT(".json")));

	UTestFunctions::DeleteFileIfExists(DirectoryName, FileName, TEXT(".json"));

	FFileHelper::SaveStringToFile(OutputString, *PathToFile,FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

FPlayerSavedData USavingAndLoadingSystem::LoadPlayerInfo(const FString& DirectoryName, const FString& FileName)
{
	const FString ProjectDirectory = FPaths::ProjectDir();
	const FString& PathToFile= FPaths::ConvertRelativePathToFull(ProjectDirectory+DirectoryName+TEXT("/")+(FileName+TEXT(".json")));
	
	FString JsonString;

	FFileHelper::LoadFileToString(JsonString, *PathToFile);
	
	TSharedPtr<FJsonObject> JsonObject;
	
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	
	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
	{
		const TArray<TSharedPtr<FJsonValue>>& VectorArray = JsonObject->GetArrayField("PlayerPosition");
		if (VectorArray.Num() == 3)
		{
			const float X = VectorArray[0]->AsNumber();
			const float Y = VectorArray[1]->AsNumber();
			const float Z = VectorArray[2]->AsNumber();
			const int NumberOfGatheredCoins = JsonObject->GetIntegerField("NumberOfGatheredCoins");

			if (JsonObject->HasField("CurrentMap"))
			{
				const FString CurrentMapName = JsonObject->GetStringField("CurrentMap");
				return FPlayerSavedData(FVector(X,Y,Z), NumberOfGatheredCoins, CurrentMapName);
			}

			return FPlayerSavedData(FVector(X,Y,Z), NumberOfGatheredCoins);
		}
	}
	return FPlayerSavedData();
}
