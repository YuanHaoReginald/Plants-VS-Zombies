#ifndef ABSTRACTZOMBIES_H
#define ABSTRACTZOMBIES_H

#include <QObject>
#include <QLabel>
#include <QMovie>
#include "enumlist.h"

class AbstractZombies : public QObject
{
    Q_OBJECT
public:
    explicit AbstractZombies(QObject *parent = 0);
    ~AbstractZombies();
    
    ZombiesType getType();
    int getRow();
    int getWidth();
    int getHeight();
    int getPosX();
    int getPoxY();
    virtual void getAttack();
    
signals:
    void die(AbstractZombies*);
    
public slots:
    
protected:
    QLabel* ZombiesLabel;
    QMovie* ZombiesMovie;
    int blood, speed;
    int Row, width, height, PosX, PosY;
    ZombiesType m_Type;
};

#endif // ABSTRACTZOMBIES_H
