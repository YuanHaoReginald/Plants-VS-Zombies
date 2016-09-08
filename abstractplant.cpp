#include "abstractplant.h"

AbstractPlant::AbstractPlant(QObject *parent) : QObject(parent)
{
    
}

AbstractPlant::~AbstractPlant()
{
    delete PlantLabel;
    delete PlantMovie;
}

PlantType AbstractPlant::getType()
{
    return m_Type;
}

int AbstractPlant::getRow()
{
    return Row;
}

int AbstractPlant::getCulumn()
{
    return Culumn;
}

int AbstractPlant::getWidth()
{
    return width;
}

int AbstractPlant::getHeight()
{
    return height;
}

void AbstractPlant::getAttack()
{
    blood--;
    if(blood == 0)
        emit die(this);
}

void AbstractPlant::Pause()
{
    
}

void AbstractPlant::Restart()
{
    
}
