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
    int getStatus() const { return static_cast<int>(CurrentStatus); }
    
signals:
    
public slots:
    void ZombieMove();
    void Jump();
    
private slots:
    void DeleteHead();
    void DeleteBody();
    void Jump2();
    void Jump3();
    
private:
    QLabel* HeadLabel;
    QMovie* HeadMovie;
    QLabel* BodyLabel;
    QMovie* BodyMovie;
    PoleVaultingZombieStatus CurrentStatus;
};

#endif // POLEVAULTINGZOMBIE_H
