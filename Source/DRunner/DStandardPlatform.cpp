#include "DStandardPlatform.h"
#include "DSpawnCoinComp.h"
#include "Components/SphereComponent.h"

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
	
	PrimaryActorTick.bCanEverTick = true;
}

ADStandardPlatform::ADStandardPlatform(
	const EGamePlatformType PlatformTypePar,
	const EGamePlatformDirection PlatformDirectionPar,
	const EGamePlatformMovementType MovementTypePar)
		:PlatformType(PlatformTypePar),
		PlatformDirection(PlatformDirectionPar),
		MovementType(MovementTypePar)
{
	
	
}

void ADStandardPlatform::BeginPlay()
{
	Super::BeginPlay();


	const FTransform& CoinLocalisationTransform = CoinLocalisation->GetComponentTransform();
	CoinSpawnComponent->SpawnCoinActor(CoinLocalisationTransform);
}

void ADStandardPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

