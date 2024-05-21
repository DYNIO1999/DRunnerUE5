// Fill out your copyright notice in the Description page of Project Settings.
#include "Components/SphereComponent.h"
#include "DEndPointPlatform.h"

#include "DGameInstance.h"
#include "DPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "EventManager.h"

ADEndPointPlatform::ADEndPointPlatform()
{

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("PlatformMeshComp");
	MeshComp->SetupAttachment(RootComponent);

	PortalEntranceMesh = CreateDefaultSubobject<UStaticMeshComponent>("PortalEntranceMesh");
	PortalEntranceMesh->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
}

void ADEndPointPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	PortalEntranceMesh->OnComponentBeginOverlap.AddDynamic(this, &ADEndPointPlatform::OnOverlapBegin);

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
	if (OtherActor && OtherActor != this && OtherActor->IsA(ADPlayer::StaticClass()))
	{
		GetWorld()->GetTimerManager().SetTimer(OpenNewLevelDelay, this, &ADEndPointPlatform::HandlePortalEntrance, 1.0f, false);
	}
}

void ADEndPointPlatform::HandlePortalEntrance()
{
	UDGameInstance* DGameInstancePtr = Cast<UDGameInstance>(GetGameInstance());
	if(DGameInstancePtr->CurrentMap== EGameMaps::TestMap)
	{
		UE_LOG(LogTemp, Error, TEXT("FINISHED LEVEL!"));		
		DGameInstancePtr->CurrentMap = EGameMaps::MainMap;
		UGameplayStatics::OpenLevel(GetWorld(), *GetMapName(EGameMaps::MainMap));
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("FINISHED GAME!"));


		FString GatheredPointsRow = FString::Printf(TEXT("Gathered Points: %f / %f"),
			DGameInstancePtr->CurrentGatheredPoints,
			DGameInstancePtr->MaxPointsToGather);
		//Add calculation of % of tracked system	

		UTestFunctions::SaveContentToFile(FString("LoggedData"), GatheredPointsRow);
		///UEventManager::GameFinalMapEndDelegate.Broadcast();

		UWorld* World = GetWorld();
		if (World)
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
			UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, true);
		}
	}
}

