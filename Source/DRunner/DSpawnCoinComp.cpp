#include "DSpawnCoinComp.h"
#include "DCoin.h"
#include "IDManager.h"

UDSpawnCoinComp::UDSpawnCoinComp()
{

}

void UDSpawnCoinComp::SpawnCoinActor(const FTransform& NewCoinTransform, const EGamePlatformType PlatformTypePar, const EGamePlatformDirection PlatformDirectionPar)
{
	if (ActorToSpawn != nullptr)
        {
            UWorld* World = GetWorld();
			if (World != nullptr)
            {
                
                FActorSpawnParameters SpawnParams;
                SpawnParams.Owner = GetOwner(); 
				
                AActor* SpawnedActor = World->SpawnActor<AActor>(ActorToSpawn, NewCoinTransform, SpawnParams);
                if (SpawnedActor != nullptr)
                {
					//UE_LOG(LogTemp, Warning, TEXT("Spawned Coin Succcessfuly"));

                	ADCoin* CoinObject = Cast<ADCoin>(SpawnedActor);
                	const int32 CoinID  = UIDManager::GenerateNewID(); 
                	CoinObject->Initialize(CoinID, PlatformTypePar, PlatformDirectionPar);

                	
                }
            }
        }

	
}

