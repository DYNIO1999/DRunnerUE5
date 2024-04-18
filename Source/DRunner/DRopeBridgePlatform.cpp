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

	BridgeCollisionBlockerLeft = CreateDefaultSubobject<UStaticMeshComponent>("BridgeBlockerLeft");
	BridgeCollisionBlockerLeft->SetupAttachment(RootComponent);

	BridgeCollisionBlockerRight = CreateDefaultSubobject<UStaticMeshComponent>("BridgeBlockerRight");
	BridgeCollisionBlockerRight->SetupAttachment(RootComponent);

	
	LogComponent = CreateDefaultSubobject<UDLoggingComponent>(TEXT("LogComponent"));
	PrimaryActorTick.bCanEverTick = true;
	CanSwing = false;

	NumberOfPlanks =10;
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

void ADRopeBridgePlatform::ConstructBridge()
{
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
	float LastHeight =0.0;
	const FVector CurrentPosition = FVector(-400.0f,0.0f,0.0);
	
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
		BridgePlanksMeshComponents[i]->SetRelativeLocation(FVector(i * SpaceBetweenPlanks+CurrentPosition.X, CurrentPosition.Y, LastHeight));
		BridgePlanksMeshComponents[i]->OnComponentBeginOverlap.AddDynamic(this, &ADRopeBridgePlatform::OnOverlapBegin);
		BridgePlanksMeshComponents[i]->OnComponentEndOverlap.AddDynamic(this, &ADRopeBridgePlatform::OnOverlapEnd);
	}

	int middle = NumberOfPlanks/2;
	
	BridgeCollisionBlockerLeft->SetRelativeLocation(BridgePlanksMeshComponents[middle]->GetRelativeLocation() + FVector(0.0f,-220.0f,0.0f));
	BridgeCollisionBlockerLeft->SetWorldScale3D(FVector(static_cast<float>(NumberOfPlanks), 1.0, 10.0));
	
	BridgeCollisionBlockerRight->SetRelativeLocation(BridgePlanksMeshComponents[middle]->GetRelativeLocation() + FVector(0.0f,220.0f,0.0f));
	BridgeCollisionBlockerRight->SetWorldScale3D(FVector(static_cast<float>(NumberOfPlanks), 1.0, 10.0));

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
		
		if (GameInstanceRef->CurrentPlayerLeg == EGameUsedLeg::Left)
			WindDirection = FVector(-1.0f, 0.0f, 0.0f); 
		else
		{
			WindDirection = FVector(1.0f, 0.0f, 0.0f);
		}
		
		GameInstanceRef->CurrentWindDirection = WindDirection;
		RotationCooldown = GameInstanceRef->ChangeLegCooldown;
		
	}
	
	GetWorld()->GetTimerManager().SetTimer(SwapRotationTimer, this, &ADRopeBridgePlatform::SwapRotation, RotationCooldown, true);
	
}

void ADRopeBridgePlatform::CreateBridge(int NumberOfWoodenPlanks)
{
	NumberOfPlanks = NumberOfWoodenPlanks;
	ConstructBridge();
}

void ADRopeBridgePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CanSwing)
	{
		if (PlatformMovementType == EGamePlatformMovementType::Running)
		{
			WindSpeed = RunningSpeed;
		}else
		{
			WindSpeed = WalkSpeed;
		}
		
		for (const auto Plank : BridgePlanksMeshComponents)
		{
			float CurrentSpeed = GameInstanceRef->PlayerCurrentSpeed;
			FRotator NewRotation = FMath::RInterpTo(Plank->GetRelativeRotation(), TargetRotation, DeltaTime, WindSpeed*CurrentSpeed);
			Plank->SetRelativeRotation(NewRotation);
			// const FVector CurrentVelocity = WindDirection* WindSpeed *DeltaTime + 10.0;
			// Plank->SetRelativeRotation(Plank->GetRelativeRotation()+FRotator(CurrentVelocity.Y, CurrentVelocity.Z, CurrentVelocity.X));
		}
	}
}

void ADRopeBridgePlatform::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ConstructBridge();
}

void ADRopeBridgePlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
	FVector PlayerVelocityNormalized = GameInstanceRef->PlayerCurrentVelocity.GetSafeNormal();
	FVector PlatformFowardVec = GetActorForwardVector().GetSafeNormal();

	float DotResult = FVector::DotProduct(PlayerVelocityNormalized,PlatformFowardVec);
	
	

	if (OtherComp->GetName().Equals(TEXT("PRINT_LOGGING"), ESearchCase::IgnoreCase) &&  ((BridgePlanksMeshComponents.Last() == OverlappedComp && DotResult >= 0) || (BridgePlanksMeshComponents[0] == OverlappedComp && DotResult<0))) 
	{
		CanSwing = false;
		//UE_LOG(LogTemp, Error, TEXT("Overlapping end"));
		CanProduceLog =  false;
		GetWorldTimerManager().ClearTimer(LoggingCooldown);
		for (const auto Plank : BridgePlanksMeshComponents)
		{
			Plank->SetRelativeRotation(FRotator(0.0f,0.0f, 0.0f));
		}
	}
	
}

void ADRopeBridgePlatform::SwapRotation()
{
	WindDirection*=-1.0f;
	GameInstanceRef->CurrentWindDirection = WindDirection;
	const FVector CurrentVelocity = WindDirection* 10.0f;
	TargetRotation = FRotator(CurrentVelocity.Y, CurrentVelocity.Z, CurrentVelocity.X);

}

void ADRopeBridgePlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetName().Equals(TEXT("PRINT_LOGGING"), ESearchCase::IgnoreCase))
	{
		CanSwing = true;
		CanProduceLog =  true;
		UDGameInstance* DGameInstance = Cast<UDGameInstance>(GetGameInstance());
		

		switch(PlatformDirection){
		case EGamePlatformDirection::Forward:
			DGameInstance->AngleToSwing = 0.0f;
				break;
		case EGamePlatformDirection::Left:
			DGameInstance->AngleToSwing = -90.0f;
			break;
		case EGamePlatformDirection::Right:
			DGameInstance->AngleToSwing = 90.0f;
			break;
		case EGamePlatformDirection::Back:
			DGameInstance->AngleToSwing = 180.0f;
			break;
		default:
			DGameInstance->AngleToSwing = 0.0f;
			break;
		}
	
		DGameInstance->CurrentPlatformType = PlatformType;
		DGameInstance->CurrentPlatformMovementType = PlatformMovementType;
		
		GetWorldTimerManager().SetTimer(LoggingCooldown, this, &ADRopeBridgePlatform::ProduceLog, LoggingDelayInSeconds, true);
	}
}

