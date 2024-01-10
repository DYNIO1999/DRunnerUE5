#pragma once

#include "VirtuSphereClientStructs.generated.h"

USTRUCT(BlueprintType)
struct FSpherePoseEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	int64 timestamp;				//Unix timestamp in microseconds

	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	float velocity;					//[m/s]
	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	float direction;				//[deg]

	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	float velocityVectorX;			//[m/s]
	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	float velocityVectorY;			//[m/s]
	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	float velocityVectorZ;			//[rad/s]
};

USTRUCT(BlueprintType)
struct FControllerStateEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	int64 timestamp;				//Unix timestamp in microseconds

	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	int controllerId;
	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	int statusRegister;
	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	int errorRegister;

	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	float electronicVoltage;		//[V]
	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	float powerVoltage;				//[V]
	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	float powerStageTemperature;	//[deg C]
};

USTRUCT(BlueprintType)
struct FMotorStateEvent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	int64 timestamp;				//Unix timestamp in microseconds

	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	int controllerId;

	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	int motorFlags;
	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	int hallPosition;				//[counts]
	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	int encoderPosition;			//[counts]
	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	float motorVelocity;			//[RPM]
	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	float motorVoltage;				//[V]
	UPROPERTY(BlueprintReadWrite, Category = "VirtuSphereClient | Struct Variables")
	float motorCurrent;				//[A]
};