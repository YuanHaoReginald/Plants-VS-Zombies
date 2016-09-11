#ifndef BUCKETHEADZOMBIE_H
#define BUCKETHEADZOMBIE_H

#include <QLabel>
#include <QMovie>
#include "abstractzombie.h"

class BucketheadZombie : public AbstractZombie
{
    Q_OBJECT
public:
    explicit BucketheadZombie(int, int);
    ~BucketheadZombie();
    
    enum class BucketheadZombieStatus {HeadNormal, HeadEating, Normal, Eating, Die};
    
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
    BucketheadZombieStatus CurrentStatus;
};

#endif // BUCKETHEADZOMBIE_H
