// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
//#include "VirtuSphereDllHost.h"
#include "VirtuSphereClientBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UVirtuSphereClientBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Sample function", Keywords = "VirtuSphereClient sample test testing"), Category = "VirtuSphereClient")
	static float VirtuSphereClientSampleFunction(float Param);

	/*UFUNCTION(BlueprintCallable, meta = (DisplayName = "Connect to VirtuSphere", Keywords = "VirtuSphereClient connect"), Category = "VirtuSphereClient")
	static void Connect(FString host = "127.0.0.1", int port = 4445);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Disconnect from VirtuSphere", Keywords = "VirtuSphereClient disconnect"), Category = "VirtuSphereClient")
	static void Disconnect();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is connected", Keywords = "VirtuSphereClient isconnected"), Category = "VirtuSphereClient")
	static bool IsConnected();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get current ping", Keywords = "VirtuSphereClient ping"), Category = "VirtuSphereClient")
	static float GetCurrentPing();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Request SpherePose events", Keywords = "VirtuSphereClient pose"), Category = "VirtuSphereClient")
	static void RequestSpherePoseUpdates(int sendRate);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Request ControllerState events", Keywords = "VirtuSphereClient controller state"), Category = "VirtuSphereClient")
	static void RequestControllerStateUpdates(int sendRate);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Request MotorState events", Keywords = "VirtuSphereClient motor state"), Category = "VirtuSphereClient")
	static void RequestMotorStateUpdates(int sendRate);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set sphere pose", Keywords = "VirtuSphereClient set pose"), Category = "VirtuSphereClient")
	static void SetSpherePose(float velocity, float direction);
	*/
private:
	//VirtuSphereDllHost dllHost;
};
