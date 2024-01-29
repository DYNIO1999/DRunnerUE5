#pragma once

#include "CoreMinimal.h"
#include "AVirtuSphereController.h"
#include "DVirtuSphereControllerBasedCode.generated.h"

UCLASS()
class DRUNNER_API ADVirtuSphereControllerBasedCode : public AVirtuSphereController
{
	GENERATED_BODY()
	protected:
	virtual void BeginPlay() override;
    
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    
    virtual void OnConnected_Implementation() override;
    virtual void OnDisconnected_Implementation()  override;
    virtual void OnSpherePose_Implementation(FSpherePoseEvent event) override;
    virtual void OnControllerState_Implementation(FControllerStateEvent event) override;
    virtual void OnMotorState_Implementation(FMotorStateEvent event) override;

	public:
	virtual void Tick(float DeltaTime) override;
};
