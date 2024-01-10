// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <functional>
#include "VirtuSphereClientStructs.h"
#include "AVirtuSphereController.generated.h"

//TODO: Make VirtuSphereClient log category (https://dev.epicgames.com/community/snippets/Qg/defining-custom-log-categories-in-c)
class VirtuSphereDllHost;

UCLASS()
class VIRTUSPHERECLIENT_API AVirtuSphereController : public AActor
{
	GENERATED_BODY()

private:
	VirtuSphereDllHost* dllHost;
	std::function<void(int)> connectionStateChangeListener;
	std::function<void(void*)> spherePoseEventListener;
	std::function<void(void*)> controllerStateEventListener;
	std::function<void(void*)> motorStateEventListener;

public:	
	// Sets default values for this actor's properties
	AVirtuSphereController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Connect to VirtuSphere", Keywords = "VirtuSphereClient connect"), Category = "VirtuSphereClient")
	void Connect(FString host = "127.0.0.1", int port = 4445);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Disconnect from VirtuSphere", Keywords = "VirtuSphereClient disconnect"), Category = "VirtuSphereClient")
	void Disconnect();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Is connected", Keywords = "VirtuSphereClient isconnected"), Category = "VirtuSphereClient")
	bool IsConnected();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get current ping", Keywords = "VirtuSphereClient ping"), Category = "VirtuSphereClient")
	float GetCurrentPing();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Request SpherePose events", Keywords = "VirtuSphereClient pose"), Category = "VirtuSphereClient")
	void RequestSpherePoseUpdates(int sendRate = 20);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Request ControllerState events", Keywords = "VirtuSphereClient controller state"), Category = "VirtuSphereClient")
	void RequestControllerStateUpdates(int sendRate = 20);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Request MotorState events", Keywords = "VirtuSphereClient motor state"), Category = "VirtuSphereClient")
	void RequestMotorStateUpdates(int sendRate = 20);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set sphere pose", Keywords = "VirtuSphereClient set pose"), Category = "VirtuSphereClient")
	void SetSpherePose(float velocity, float direction);


	UFUNCTION(BlueprintImplementableEvent, Category = "VirtuSphereClient")
	void OnConnected();

	UFUNCTION(BlueprintImplementableEvent, Category = "VirtuSphereClient")
	void OnDisconnected();

	UFUNCTION(BlueprintImplementableEvent, Category = "VirtuSphereClient")
	void OnSpherePose(FSpherePoseEvent event);

	UFUNCTION(BlueprintImplementableEvent, Category = "VirtuSphereClient")
	void OnControllerState(FControllerStateEvent event);

	UFUNCTION(BlueprintImplementableEvent, Category = "VirtuSphereClient")
	void OnMotorState(FMotorStateEvent event);
};
