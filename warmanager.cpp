#include "warmanager.h"
#include "sunflower.h"
#include "globalmanager.h"
#include "managermanager.h"
#include "enumlist.h"

WarManager::WarManager(QObject *parent) : QObject(parent)
{
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            grass[i][j] = nullptr;
        }
    }
}

void WarManager::RaisePlant(int RowVal, int CulumnVal, PlantType tempType)
{
    SunFlower* temp;
    switch (tempType) 
    {
    case PlantType::SunFlower:
        temp = new SunFlower(RowVal, CulumnVal);
        grass[RowVal - 1][CulumnVal - 1] = temp; 
        connect(temp, SIGNAL(ProduceSun(int,int)),
                ManagerManager::GlobalSunManager, SLOT(FlowerSun(int,int)));
        emit CostSun(50);
        break;
    case PlantType::Peashooter:
        
        break;
    case PlantType::WallNut:
        
        break;
    case PlantType::Chomper:
        
        break;
    default:
        break;
    }
}
