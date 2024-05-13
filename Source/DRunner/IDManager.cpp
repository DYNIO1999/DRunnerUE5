#include "IDManager.h"

int32 UIDManager::ID = 1;

void UIDManager::ResetID()
{
	ID = 1;
}
