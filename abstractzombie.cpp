#include "abstractzombie.h"

AbstractZombie::AbstractZombie(QObject *parent) : QObject(parent)
{
    
}

AbstractZombie::~AbstractZombie()
{
    delete ZombieLabel;
    delete ZombieMovie;
}

ZombieType AbstractZombie::getType()
{
    return m_Type;
}

int AbstractZombie::getRow()
{
    return Row;
}

int AbstractZombie::getWidth()
{
    return width;
}

int AbstractZombie::getHeight()
{
    return height;
}

int AbstractZombie::getPosX()
{
    return PosX;
}

int AbstractZombie::getPoxY()
{
    return PosY;
}

void AbstractZombie::getAttack()
{
    blood--;
    if(blood <= 0)
        emit die(this);
}
