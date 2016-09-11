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
    explicit AbstractZombie(QObject *parent = 0) : QObject(parent) { }
    ~AbstractZombie();
    
    ZombieType getType() const { return ThisZombieType; }
    int getRow() const { return Row; }
    int getWidth() const { return Width; }
    int getHeight() const { return Height; }
    int getPosX() const { return PosX; }
    int getPoxY() const { return PosY; }
    int getSpeed() const { return Speed; }
    virtual void getAttack();
    
    int id;
    
signals:
    void die(AbstractZombie*, int);
    
protected:
    QLabel* ZombieLabel;
    QMovie* ZombieMovie;
    int Blood, Speed;
    int Row, Width, Height, PosX, PosY;
    ZombieType ThisZombieType;
};

#endif // ABSTRACTZOMBIES_H
