#include "abstractzombies.h"

AbstractZombies::AbstractZombies(QObject *parent) : QObject(parent)
{
    
}

AbstractZombies::~AbstractZombies()
{
    delete ZombiesLabel;
    delete ZombiesMovie;
}

ZombiesType AbstractZombies::getType()
{
    return m_Type;
}

int AbstractZombies::getRow()
{
    return Row;
}

int AbstractZombies::getWidth()
{
    return width;
}

int AbstractZombies::getHeight()
{
    return height;
}

int AbstractZombies::getPosX()
{
    return PosX;
}

int AbstractZombies::getPoxY()
{
    return PosY;
}

void AbstractZombies::getAttack()
{
    blood--;
    if(blood <= 0)
        emit die(this);
}
