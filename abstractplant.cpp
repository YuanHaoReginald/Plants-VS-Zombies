#include "abstractplant.h"

AbstractPlant::~AbstractPlant()
{
    delete PlantLabel;
    delete PlantMovie;
}

void AbstractPlant::getAttack()
{
    Blood--;
    if(Blood == 0)
        emit die(this);
}
