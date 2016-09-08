#include "warmanager.h"
#include "sunflower.h"
#include "wallnut.h"
#include "peashooter.h"
#include "pea.h"
#include "globalmanager.h"
#include "managermanager.h"
#include "enumlist.h"
#include "normalzombie.h"
#include "bucketheadzombie.h"
#include "polevaultingzombie.h"
#include <QtGlobal>
#include <QTime>

WarManager::WarManager(QObject *parent) : QObject(parent)
{
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            grass[i][j] = nullptr;
        }
    }
    WarClock = new QTimer;
    WarClock->setInterval(5);
    connect(WarClock, SIGNAL(timeout()), this, SLOT(ClockUpdate()));
    
    firstZombie = 0;
    lastZombie = 0;
    GenerateZombieClockNow = 0;
    GenerateZombieClockLimit = 5000;
    
    WarClock->start();
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

void WarManager::GeneratePea(int RowVal, int CulumnVal)
{
    Pea* temp = new Pea(RowVal, CulumnVal);
    ManagerManager::GlobalSunManager->UpAllSun();
    PeaManager[RowVal - 1].push_back(temp);
    connect(temp, SIGNAL(die(Pea*)), this, SLOT(DeletePea(Pea*)));
}

void WarManager::GenerateZombie()
{
    GenerateZombieClockNow = 0;
    lastZombie++;
    if(lastZombie >= 0 && lastZombie < 10)
        GenerateZombieClockLimit = 5000;
    else if(lastZombie >= 10 && lastZombie < 20)
        GenerateZombieClockLimit = 4000;
    else if(lastZombie >= 20 && lastZombie < 30)
        GenerateZombieClockLimit = 3000;
    else if(lastZombie >= 30 && lastZombie < 40)
        GenerateZombieClockLimit = 2000;
    else if(lastZombie >= 40 && lastZombie < 50)
        GenerateZombieClockLimit = 1000;
    else if(lastZombie >= 50 && lastZombie < 60)
        GenerateZombieClockLimit = 500;
    else if(lastZombie >= 60 && lastZombie < 80)
        GenerateZombieClockLimit = 400;
    else if(lastZombie >= 80 && lastZombie < 100)
        GenerateZombieClockLimit = 300;
    else if(lastZombie >= 100 && lastZombie < 120)
        GenerateZombieClockLimit = 200;
    else if(lastZombie >= 120 && lastZombie < 150)
        GenerateZombieClockLimit = 100;
    
    qsrand(QTime::currentTime().msecsSinceStartOfDay());
    int templine = qrand() % 5 + 1;
    if(GlobalManager::ZombieLine[lastZombie - 1] == 1)
        ZombieManager[lastZombie - 1] = new NormalZombie(templine, lastZombie);
    else if(GlobalManager::ZombieLine[lastZombie - 1] == 2)
        ZombieManager[lastZombie - 1] = new BucketheadZombie(templine, lastZombie);
    else if(GlobalManager::ZombieLine[lastZombie - 1] == 3)
        ZombieManager[lastZombie - 1] = new PoleVaultingZombie(templine, lastZombie);
    ManagerManager::GlobalSunManager->UpAllSun();    
    
    lastZombie++;
}

void WarManager::ClockUpdate()
{
    //检查部分
    
    //更新坐标
    if(lastZombie != 150)
    {
        if(lastZombie % 10 != 0 || (lastZombie % 10 == 0 && lastZombie == firstZombie))
        {
            GenerateZombieClockNow += 5;
            if(GenerateZombieClockNow == GenerateZombieClockLimit)
            {
                GenerateZombie();
            }
        }
    }
}

void WarManager::RaisePlant(int RowVal, int CulumnVal, PlantType tempType)
{
    SunFlower* temp1;
    WallNut* temp2;
    Peashooter* temp3;
    switch (tempType) 
    {
    case PlantType::SunFlower:
        temp1 = new SunFlower(RowVal, CulumnVal);
        ManagerManager::GlobalSunManager->UpAllSun();
        grass[RowVal - 1][CulumnVal - 1] = temp1; 
        connect(temp1, SIGNAL(ProduceSun(int,int)),
                ManagerManager::GlobalSunManager, SLOT(FlowerSun(int,int)));
        connect(temp1, SIGNAL(die(AbstractPlant*)), this, SLOT(DeletePlant(AbstractPlant*)));
        emit CostSun(50);
        break;
    case PlantType::Peashooter:
        temp3 = new Peashooter(RowVal, CulumnVal);
        ManagerManager::GlobalSunManager->UpAllSun();
        grass[RowVal - 1][CulumnVal - 1] = temp3;
        connect(temp3, SIGNAL(EmitPea(int,int)),
                this, SLOT(GeneratePea(int,int)));
        connect(temp3, SIGNAL(die(AbstractPlant*)), this, SLOT(DeletePlant(AbstractPlant*)));
        emit CostSun(100);
        break;
    case PlantType::WallNut:
        temp2 = new WallNut(RowVal, CulumnVal);
        ManagerManager::GlobalSunManager->UpAllSun();
        grass[RowVal - 1][CulumnVal - 1] = temp2; 
        connect(temp2, SIGNAL(die(AbstractPlant*)), this, SLOT(DeletePlant(AbstractPlant*)));
        emit CostSun(50);
        break;
    default:
        break;
    }
}

void WarManager::DeletePlant(AbstractPlant* m_point)
{
    delete m_point;
}

void WarManager::DeletePea(Pea * m_Pea)
{
    delete m_Pea;
}
