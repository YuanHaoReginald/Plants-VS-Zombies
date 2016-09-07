#include "cardmanager.h"
#include "globalmanager.h"
#include "plantcard.h"
#include <vector>

CardManager::CardManager(QObject *parent) : QObject(parent)
{
    PlantCard* temp = new PlantCard(PlantType::SunFlower, 1);
    CardVec.push_back(temp);
    connect(this, SIGNAL(Pause()), temp, SLOT(Pause()));
    connect(this, SIGNAL(Restart()), temp, SLOT(Restart()));
    connect(this, SIGNAL(CheckAllCard()), temp, SLOT(CheckThis()));
    temp = new PlantCard(PlantType::Peashooter, 2);
    CardVec.push_back(temp);
    connect(this, SIGNAL(Pause()), temp, SLOT(Pause()));
    connect(this, SIGNAL(Restart()), temp, SLOT(Restart()));
    connect(this, SIGNAL(CheckAllCard()), temp, SLOT(CheckThis()));
    temp = new PlantCard(PlantType::WallNut, 3);
    CardVec.push_back(temp);
    connect(this, SIGNAL(Pause()), temp, SLOT(Pause()));
    connect(this, SIGNAL(Restart()), temp, SLOT(Restart()));
    connect(this, SIGNAL(CheckAllCard()), temp, SLOT(CheckThis()));
    temp = new PlantCard(PlantType::Chomper, 4);
    CardVec.push_back(temp);
    connect(this, SIGNAL(Pause()), temp, SLOT(Pause()));
    connect(this, SIGNAL(Restart()), temp, SLOT(Restart()));
    connect(this, SIGNAL(CheckAllCard()), temp, SLOT(CheckThis()));
}

CardManager::~CardManager()
{
    for(auto ch : CardVec)
    {
        delete ch;
    }
}

void CardManager::FreezeSomeone(PlantType TypeVal)
{
    for(auto ca : CardVec)
    {
        if(ca->getType() == TypeVal)
        {
            ca->FreezeThis();
            break;
        }
    }
}
