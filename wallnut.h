#ifndef WALLNUT_H
#define WALLNUT_H

#include "abstractplant.h"

class WallNut : public AbstractPlant
{
public:
    WallNut(int RowVal, int CulumnVal);
    ~WallNut();
    
    enum class WallNutStatus { Normal, Crash1, Crash2 };
    
    void getAttack();
    
private:
    void checkStatus();
    WallNutStatus CurrentStatus;
};

#endif // WALLNUT_H
