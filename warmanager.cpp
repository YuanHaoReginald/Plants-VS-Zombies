#include "warmanager.h"
#include "sunflower.h"
#include "wallnut.h"
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

WarManager::~WarManager()
{
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            delete grass[i][j];
        }
    }
}

void WarManager::RaisePlant(int RowVal, int CulumnVal, PlantType tempType)
{
    SunFlower* temp1;
    WallNut* temp2;
    switch (tempType) 
    {
    case PlantType::SunFlower:
        temp1 = new SunFlower(RowVal, CulumnVal);
        grass[RowVal - 1][CulumnVal - 1] = temp1; 
        connect(temp1, SIGNAL(ProduceSun(int,int)),
                ManagerManager::GlobalSunManager, SLOT(FlowerSun(int,int)));
        connect(temp1, SIGNAL(die(AbstractPlant*)), this, SLOT(DeletePlant(AbstractPlant*)));
        emit CostSun(50);
        break;
    case PlantType::Peashooter:
        
        break;
    case PlantType::WallNut:
        temp2 = new WallNut(RowVal, CulumnVal);
        grass[RowVal - 1][CulumnVal - 1] = temp2; 
        connect(temp2, SIGNAL(die(AbstractPlant*)), this, SLOT(DeletePlant(AbstractPlant*)));        
        break;
    default:
        break;
    }
}

void WarManager::DeletePlant(AbstractPlant* m_point)
{
    delete m_point;
}
