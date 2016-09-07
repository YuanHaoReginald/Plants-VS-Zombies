#include "managermanager.h"

ManagerManager::ManagerManager()
{
    
}

SunManager *ManagerManager::GlobalSunManager = nullptr;
CardManager *ManagerManager::GlobalCardManager = nullptr;
WarManager *ManagerManager::GlobalWarManager = nullptr;
