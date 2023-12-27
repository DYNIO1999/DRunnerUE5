#include "DSpawnCoinComp.h"

UDSpawnCoinComp::UDSpawnCoinComp()
{

}

void UDSpawnCoinComp::SpawnCoinActor(const FTransform& NewCoinTransform)
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
					UE_LOG(LogTemp, Warning, TEXT("Spawned Coin Succcessfuly"));
                }
            }
        }

	
}

