// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "IDManager.generated.h"

UCLASS()
class DRUNNER_API UIDManager : public UObject
{
	GENERATED_BODY()
public:
	static void ResetID();
	static int32 GenerateNewID() {
		return ID++;
	}
private:
	static int32 ID;
};
