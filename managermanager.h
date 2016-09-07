#ifndef MANAGERMANAGER_H
#define MANAGERMANAGER_H

#include "cardmanager.h"
#include "sunmanager.h"
#include "warmanager.h"

class ManagerManager
{
private:
    ManagerManager();
    
public:
    static SunManager *GlobalSunManager;
    static CardManager *GlobalCardManager;
    static WarManager *GlobalWarManager;
    
};

#endif // MANAGERMANAGER_H
