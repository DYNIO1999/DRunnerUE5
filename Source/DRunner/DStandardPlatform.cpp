#include "DStandardPlatform.h"

#include "DGameInstance.h"
#include "DSpawnCoinComp.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "DLoggingComponent.h"

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

	StandardPlatformAmbientSound = CreateDefaultSubobject<UAudioComponent>(TEXT("StandardPlatformAmbientSound"));
	StandardPlatformAmbientSound->SetupAttachment(RootComponent);
	StandardPlatformAmbientSound->bAutoActivate = false;
	
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
	const FTransform& CoinLocalisationTransform = CoinLocalisation->GetComponentTransform();
	CoinSpawnComponent->SpawnCoinActor(CoinLocalisationTransform, PlatformType, PlatformDirection);
}

void ADStandardPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComp->OnComponentBeginOverlap.AddDynamic(this, &ADStandardPlatform::OnOverlapBegin);
	MeshComp->OnComponentEndOverlap.AddDynamic(this, &ADStandardPlatform::OnOverlapEnd);
	CanProduceLog = false;
	LoggingDelayInSeconds =0.1f;
}

void ADStandardPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADStandardPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->GetName().Equals(TEXT("PRINT_LOGGING"), ESearchCase::IgnoreCase))
	{
		CanProduceLog =  true;
		UDGameInstance* DGameInstance = Cast<UDGameInstance>(GetGameInstance());
		
		DGameInstance->CurrentPlatformType = PlatformType;
		DGameInstance->CurrentPlatformMovementType = PlatformMovementType;

		if(not StandardPlatformAmbientSound->IsPlaying())
		{
			StandardPlatformAmbientSound->Play();
		}
		
		GetWorldTimerManager().SetTimer(MyTimerHandle, this, &ADStandardPlatform::ProduceLog, LoggingDelayInSeconds, true);
	}
}

void ADStandardPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp->GetName().Equals(TEXT("PRINT_LOGGING"), ESearchCase::IgnoreCase))
	{
		CanProduceLog =  false;

		if(StandardPlatformAmbientSound->IsPlaying())
		{
			StandardPlatformAmbientSound->Stop();
		}

		GetWorldTimerManager().ClearTimer(MyTimerHandle);
	}
}

void ADStandardPlatform::ProduceLog()
{
	if(CanProduceLog)
	{
		LogComponent->SaveLoggedData(
			static_cast<int>(PlatformType),
			static_cast<int>(PlatformDirection),
			static_cast<int>(PlatformMovementType));
	}
}

