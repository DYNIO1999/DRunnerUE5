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
}

void ADStandardPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADStandardPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherActor->IsA(ADPlayer::StaticClass()))
	{
		UE_LOG(LogTemp, Warning, TEXT("SAVED TO FILE"));
		LogComponent->SaveLoggedData();
	}
}

