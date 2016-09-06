#include "abstractplant.h"

AbstractPlant::AbstractPlant(QObject *parent) : QObject(parent)
{
    
}

AbstractPlant::~AbstractPlant()
{
    
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

PlantType AbstractPlant::getAttack()
{
    blood--;
    if(blood == 0)
        emit die();
}
