#include "abstractzombie.h"

AbstractZombie::~AbstractZombie()
{
    delete ZombieLabel;
    delete ZombieMovie;
}

void AbstractZombie::getAttack()
{
    Blood--;
    if(Blood == 0)
        emit die(this, id);
}
