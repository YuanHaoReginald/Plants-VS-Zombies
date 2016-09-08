#ifndef NORMALZOMBIES_H
#define NORMALZOMBIES_H

#include "abstractzombie.h"

class NormalZombie : public AbstractZombie
{
    Q_OBJECT
public:
    explicit NormalZombie(int, int);
    ~NormalZombie();
    
signals:
    
public slots:
};

#endif // NORMALZOMBIES_H
