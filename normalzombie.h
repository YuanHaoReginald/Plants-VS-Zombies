#ifndef NORMALZOMBIES_H
#define NORMALZOMBIES_H

#include "abstractzombie.h"
#include <QLabel>
#include <QMovie>

class NormalZombie : public AbstractZombie
{
    Q_OBJECT
public:
    explicit NormalZombie(int, int);
    ~NormalZombie();
    
    enum class NormalZombieStatus {Normal, Eating, Die};
    
    void getAttack();
    void SwitchStatus();
    int getStatus() const { return static_cast<int>(CurrentStatus); }

public slots:
    void ZombieMove();
    
private slots:
    void DeleteHead();
    void DeleteBody();
    
private:
    QLabel* HeadLabel;
    QMovie* HeadMovie;
    QLabel* BodyLabel;
    QMovie* BodyMovie;
    NormalZombieStatus CurrentStatus;
};

#endif // NORMALZOMBIES_H
