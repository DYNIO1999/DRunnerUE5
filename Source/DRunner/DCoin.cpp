// Fill out your copyright notice in the Description page of Project Settings.


#include "DCoin.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DPlayer.h"
// Sets default values
ADCoin::ADCoin()
{

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("CoinGatheredCollisionProfile");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
	
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ADCoin::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ADCoin::OnOverlapBegin);
}

// Called every frame
void ADCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADCoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor && OtherActor != this && OtherActor->IsA(ADPlayer::StaticClass()))
	{
		SendInfoGathered();
		Destroy();
	}
}

void ADCoin::SendInfoGathered() const
{
	OnEventGathered.Broadcast();
}

