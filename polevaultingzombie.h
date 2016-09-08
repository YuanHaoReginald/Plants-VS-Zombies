#ifndef POLEVAULTINGZOMBIE_H
#define POLEVAULTINGZOMBIE_H

#include "abstractzombie.h"
#include <QLabel>
#include <QMovie>

class PoleVaultingZombie : public AbstractZombie
{
    Q_OBJECT
public:
    explicit PoleVaultingZombie(int, int);
    ~PoleVaultingZombie();
    
    enum class PoleVaultingZombieStatus {Pole, Jump, Normal, Eating, Die};
    
    void getAttack();
    void SwitchStatus();
    int getStatus();
    
signals:
    
public slots:
    void ZombieMove();
    void jump();
    
private slots:
    void DeleteHead();
    void DeleteBody();
    void jump2();
    void jump3();
    
private:
    QLabel* HeadLabel;
    QMovie* HeadMovie;
    QLabel* BodyLabel;
    QMovie* BodyMovie;
    PoleVaultingZombieStatus m_status;
};

#endif // POLEVAULTINGZOMBIE_H
