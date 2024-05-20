// Fill out your copyright notice in the Description page of Project Settings.
#include "Components/SphereComponent.h"
#include "DEndPointPlatform.h"


ADEndPointPlatform::ADEndPointPlatform()
{

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("PlatformMeshComp");
	MeshComp->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
	
}

void ADEndPointPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &ADEndPointPlatform::OnOverlapBegin);
	MeshComp->OnComponentEndOverlap.AddDynamic(this, &ADEndPointPlatform::OnOverlapEnd);

}

void ADEndPointPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADEndPointPlatform::InitializePlatform(const EGamePlatformType PlatformTypePar,
	const EGamePlatformDirection PlatformDirectionPar, const EGamePlatformMovementType MovementTypePar)
{
	PlatformType = PlatformTypePar;
	PlatformDirection =  PlatformDirectionPar;
	PlatformMovementType= MovementTypePar;
}

void ADEndPointPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ADEndPointPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

