#include "DCoin.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EventManager.h"
#include "DPlayer.h"
#include "DGamePlatformEnums.h"
#include "Camera/CameraComponent.h"

ADCoin::ADCoin()
{

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("CoinGatheredCollisionProfile");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

	CoinID = -1;
	AllowedOffsetLimit = 0.1f;

	PrimaryActorTick.bCanEverTick = true;
}

void ADCoin::BeginPlay()
{
	Super::BeginPlay();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ADCoin::OnOverlapBegin);
}

void ADCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADCoin::Initialize(const int32 ID, const EGamePlatformType PlatformTypePar, const EGamePlatformDirection PlatformDirectionPar)
{
	CoinID = ID;
	PlatformType = PlatformTypePar;
	PlatformDirection=  PlatformDirectionPar;
}

void ADCoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor && OtherActor != this && OtherActor->IsA(ADPlayer::StaticClass()))
	{

		FVector PlayerFowardVector;
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			ACharacter* PlayerCharacter = Cast<ACharacter>(PlayerController->GetPawn());
			if (PlayerCharacter)
			{
				UCameraComponent* CameraComponent = PlayerCharacter->FindComponentByClass<UCameraComponent>();
				if (CameraComponent)
				{
					PlayerFowardVector = CameraComponent->GetForwardVector();
					
				}
			}
		}

		const FVector  PlatformForwardDir= FVector(1.0,0.0,0.0);
		float Angle = GetAngleBasedOnPlatformDirection(PlatformType, PlatformDirection);

		if (PlatformType == EGamePlatformType::RightPlatform)
		{
			Angle+=90.0f;
		}else if(PlatformType == EGamePlatformType::LeftPlatform)
		{
			Angle-=90.0f;
		}
		FRotator NewRotator(0.f, Angle, 0.f);
		FVector RotatedVector = NewRotator.RotateVector(PlatformForwardDir);


		const FVector ResultVector = FVector::CrossProduct(PlayerFowardVector, RotatedVector);
				
		if( ResultVector.Z < AllowedOffsetLimit  && ResultVector.Z >-AllowedOffsetLimit){
			//UE_LOG(LogTemp, Error, TEXT("OKAY MIDDLE X:%f, Y:%f, Z:%f"), ResultVector.X,ResultVector.Y, ResultVector.Z);
			SendInfoGathered(1.0f, EGameGatheredFromDirection::Middle, CoinID);
		}
		else if(ResultVector.Z > AllowedOffsetLimit)
		{

			SendInfoGathered(0.5f, EGameGatheredFromDirection::Right, CoinID);
			//UE_LOG(LogTemp, Error, TEXT("RIGHT"));

		}else
		{
			SendInfoGathered(0.5f, EGameGatheredFromDirection::Left, CoinID);
			//UE_LOG(LogTemp, Error, TEXT("LEFT"));
		}
		
		Destroy();
		
	}

}

void ADCoin::SendInfoGathered(const float MultiplayerPerPoint, const EGameGatheredFromDirection GatheredFromDirection, const int32 ID) const
{
	OnEventGathered.Broadcast(MultiplayerPerPoint);
	UEventManager::CoinGatheredFromDirectionDelegate.Broadcast(GatheredFromDirection, ID);

	if(UEventManager::PlaySoundGatheredDelegate.IsBound())
	{
		UEventManager::PlaySoundGatheredDelegate.Broadcast();
	}
	
}
