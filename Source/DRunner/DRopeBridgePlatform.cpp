#include "DRopeBridgePlatform.h"
#include "CableComponent.h"
#include "Components/SphereComponent.h"
#include "DLoggingComponent.h"
#include "Kismet/GameplayStatics.h"


ADRopeBridgePlatform::ADRopeBridgePlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("CoinGatheredCollisionProfile");
	RootComponent = SphereComp;

	MeshToCheckCollision = CreateDefaultSubobject<UStaticMeshComponent>("RopeBridgeCore");
	MeshToCheckCollision->SetupAttachment(RootComponent);


	BridgeStart = CreateDefaultSubobject<UStaticMeshComponent>("BridgeStart");
	BridgeStart->SetupAttachment(RootComponent);

	BridgeEnd = CreateDefaultSubobject<UStaticMeshComponent>("BridgeEnd");
	BridgeEnd->SetupAttachment(RootComponent);

	
	LogComponent = CreateDefaultSubobject<UDLoggingComponent>(TEXT("LogComponent"));
	PrimaryActorTick.bCanEverTick = true;

}

void ADRopeBridgePlatform::InitializePlatform(const EGamePlatformType PlatformTypePar,
	const EGamePlatformDirection PlatformDirectionPar, const EGamePlatformMovementType MovementTypePar)
{
	PlatformType = PlatformTypePar;
	PlatformDirection =  PlatformDirectionPar;
	PlatformMovementType= MovementTypePar;
}

void ADRopeBridgePlatform::ProduceLog()
{
	if(CanProduceLog)
	{
		LogComponent->SaveLoggedData(
			static_cast<int>(PlatformType),
			static_cast<int>(PlatformDirection),
			static_cast<int>(PlatformMovementType));
	}
}

void ADRopeBridgePlatform::BeginPlay()
{
	Super::BeginPlay();

	
	CanProduceLog = false;
	LoggingDelayInSeconds =0.1f;


	UDGameInstance* DGameInstance = Cast<UDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(DGameInstance)
	{
		GameInstanceRef = DGameInstance;
		GameInstanceRef->CurrentWindDirection = WindDirection;
	}
	
	
	GetWorld()->GetTimerManager().SetTimer(SwapRotationTimer, this, &ADRopeBridgePlatform::SwapRotation, RotationCooldown, true);
	
}

void ADRopeBridgePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (const auto Plank : BridgePlanksMeshComponents)
	{
		const FVector CurrentVelocity = WindDirection* WindSpeed *DeltaTime;
		Plank->SetRelativeRotation(Plank->GetRelativeRotation()+FRotator(CurrentVelocity.Y, CurrentVelocity.Z, CurrentVelocity.X));
	}

	//UE_LOG(LogTemp, Warning, TEXT("WIND %f %f %f"), WindDirection.X, WindDirection.Y, WindDirection.Z);
	
}

void ADRopeBridgePlatform::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	for (UStaticMeshComponent* Component : BridgePlanksMeshComponents)
	{
		if (Component)
		{
			Component->DestroyComponent();
		}
	}
	BridgePlanksMeshComponents.Empty(); 

	for (UCableComponent* CableComp : Ropes)
	{
		if(CableComp){
			CableComp->DestroyComponent();
		}
	}
	Ropes.Empty();

	for(size_t i =0; i< NumberOfPlanks;i++)
	{
		UStaticMeshComponent* MeshComponent = NewObject<UStaticMeshComponent>(this);

		MeshComponent->SetStaticMesh(PlankMeshReference);
		MeshComponent->RegisterComponent();
		MeshComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

		BridgePlanksMeshComponents.Add(MeshComponent);
	}

	const float MiddlePosition = NumberOfPlanks / 2.0f ;
	float HalfDistance = MiddlePosition* SpaceBetweenPlanks;
	float LastHeight =0.0;
	const FVector CurrentPosition = FVector::Zero();
	
	for(size_t i =0; i< NumberOfPlanks;i++)
	{
		if (i < MiddlePosition)
		{
			LastHeight -=HeightOffset;
		}
		else
		{
			LastHeight +=HeightOffset;
		}
		BridgePlanksMeshComponents[i]->SetRelativeLocation(FVector(i * SpaceBetweenPlanks - HalfDistance, CurrentPosition.Y, LastHeight));
		BridgePlanksMeshComponents[i]->OnComponentBeginOverlap.AddDynamic(this, &ADRopeBridgePlatform::OnOverlapBegin);
		BridgePlanksMeshComponents[i]->OnComponentEndOverlap.AddDynamic(this, &ADRopeBridgePlatform::OnOverlapEnd);
	}


	BridgeStart->SetRelativeLocation(FVector(BridgePlanksMeshComponents[0]->GetRelativeLocation().X-100.0f, CurrentPosition.Y, CurrentPosition.Z));

	
	BridgeEnd->SetRelativeLocation(FVector(BridgePlanksMeshComponents.Last()->GetRelativeLocation().X+100.0f, CurrentPosition.Y, CurrentPosition.Z));

	for(size_t i =0; i< 2;i++)
	{
		UCableComponent* CableComponent = NewObject<UCableComponent>(this);
	
		if (CableComponent)
		{
			CableComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			CableComponent->RegisterComponent(); 
			Ropes.Add(CableComponent);
		}
	}

	for (const auto Rope : Ropes)
	{
		Rope->SetMaterial(0, RopeMaterialReference);
		Rope->CableGravityScale = RopeGravityScale;
	}

	Ropes[0]->SetRelativeLocation(FVector(BridgeStart->GetRelativeLocation().X, BridgeStart->GetRelativeLocation().Y +160.0f , BridgeStart->GetRelativeLocation().Z+60.0f));
	Ropes[1]->SetRelativeLocation(FVector(BridgeStart->GetRelativeLocation().X, BridgeStart->GetRelativeLocation().Y -160.0f , BridgeStart->GetRelativeLocation().Z+60.0f));

	Ropes[0]->EndLocation = FVector(BridgeEnd->GetRelativeLocation().X, BridgeEnd->GetRelativeLocation().Y +160.0f , BridgeEnd->GetRelativeLocation().Z+60.0f);
	Ropes[1]->EndLocation = FVector(BridgeEnd->GetRelativeLocation().X, BridgeEnd->GetRelativeLocation().Y -160.0f , BridgeEnd->GetRelativeLocation().Z+60.0f);

	for (const auto Plank : BridgePlanksMeshComponents)
	{
		const FVector CurrentVelocity = WindDirection* WindSpeed* -1.0f;
		Plank->SetRelativeRotation(Plank->GetRelativeRotation()+FRotator(CurrentVelocity.Y, CurrentVelocity.Z, CurrentVelocity.X));
	}


	
	
}

void ADRopeBridgePlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp->GetName().Equals(TEXT("PRINT_LOGGING"), ESearchCase::IgnoreCase))
	{
		UE_LOG(LogTemp, Error, TEXT("Overlapping begin"));
		CanProduceLog =  false;
		GetWorldTimerManager().ClearTimer(LoggingCooldown);
	}
	
}

void ADRopeBridgePlatform::SwapRotation()
{
	WindDirection*=-1.0f;
	GameInstanceRef->CurrentWindDirection = WindDirection;

}

void ADRopeBridgePlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetName().Equals(TEXT("PRINT_LOGGING"), ESearchCase::IgnoreCase))
	{
		CanProduceLog =  true;
		UDGameInstance* DGameInstance = Cast<UDGameInstance>(GetGameInstance());
		
		DGameInstance->CurrentPlatformType = PlatformType;
		GetWorldTimerManager().SetTimer(LoggingCooldown, this, &ADRopeBridgePlatform::ProduceLog, LoggingDelayInSeconds, true);
	}
}

