#include "DStandardPlatform.h"
#include "DSpawnCoinComp.h"
#include "Components/SphereComponent.h"
#include "DLoggingComponent.h"
#include "DPlayer.h"

ADStandardPlatform::ADStandardPlatform()
{

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");

	RootComponent = SphereComp;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(RootComponent);

	CoinLocalisation= CreateDefaultSubobject<UStaticMeshComponent>("CoinLocalisation");
	CoinLocalisation->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CoinLocalisation->SetupAttachment(RootComponent);
	
	CoinSpawnComponent = CreateDefaultSubobject<UDSpawnCoinComp>(TEXT("CoinSpawnComponent"));

	LogComponent = CreateDefaultSubobject<UDLoggingComponent>(TEXT("LogComponent"));
	PrimaryActorTick.bCanEverTick = true;
}

void ADStandardPlatform::InitializePlatform(
	const EGamePlatformType PlatformTypePar,
	const EGamePlatformDirection PlatformDirectionPar,
	const EGamePlatformMovementType MovementTypePar)
{
	PlatformType = PlatformTypePar;
	PlatformDirection =  PlatformDirectionPar;
	PlatformMovementType= MovementTypePar;
}

void ADStandardPlatform::BeginPlay()
{
	Super::BeginPlay();


	const FTransform& CoinLocalisationTransform = CoinLocalisation->GetComponentTransform();
	CoinSpawnComponent->SpawnCoinActor(CoinLocalisationTransform);

	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &ADStandardPlatform::OnOverlapBegin);
	MeshComp->OnComponentEndOverlap.AddDynamic(this, &ADStandardPlatform::OnOverlapEnd);
	CanProduceLog = false;
	LoggingDelayInSeconds =0.1f;
}

void ADStandardPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// if(CanProduceLog)
	// {
	// 	ProduceLog();
	// }
}

void ADStandardPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetName().Equals(TEXT("PRINT_LOGGING"), ESearchCase::IgnoreCase))
	{
		//UE_LOG(LogTemp, Error, TEXT("STARTED COLLIDING"));
		CanProduceLog =  true;
		GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ADStandardPlatform::ProduceLog, LoggingDelayInSeconds, true);
	}
}

void ADStandardPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp->GetName().Equals(TEXT("PRINT_LOGGING"), ESearchCase::IgnoreCase))
	{
		CanProduceLog =  false;
		GetWorldTimerManager().ClearTimer(MyTimerHandle);
	}
}

void ADStandardPlatform::ProduceLog()
{
	if(CanProduceLog)
	{
		//get player location?
		LogComponent->SaveLoggedData(
			static_cast<int>(PlatformType),
			static_cast<int>(PlatformDirection),
			static_cast<int>(PlatformMovementType));
	}
}

