#ifndef ABSTRACTZOMBIES_H
#define ABSTRACTZOMBIES_H

#include <QObject>
#include <QLabel>
#include <QMovie>
#include "enumlist.h"

class AbstractZombie : public QObject
{
    Q_OBJECT
public:
    explicit AbstractZombie(QObject *parent = 0);
    ~AbstractZombie();
    
    ZombieType getType();
    int getRow();
    int getWidth();
    int getHeight();
    int getPosX();
    int getPoxY();
    int getSpeed();
    virtual void getAttack();
    
    int id;
    
signals:
    void die(AbstractZombie*, int);
    
public slots:
    
protected:
    QLabel* ZombieLabel;
    QMovie* ZombieMovie;
    int blood, speed;
    int Row, width, height, PosX, PosY;
    ZombieType m_Type;
};

#endif // ABSTRACTZOMBIES_H
