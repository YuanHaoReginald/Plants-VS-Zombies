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
    
    enum class BucketheadZombieStatus {HeadNormal, HeadEating, Normal, Eating};
    
    void getAttack();
    void SwitchStatus();
    int getStatus();
    
signals:
    
public slots:
    int ZombieMove();
    
private slots:
    void DeleteHead();
    void DeleteBody();
    
private:
    QLabel* HeadLabel;
    QMovie* HeadMovie;
    QLabel* BodyLabel;
    QMovie* BodyMovie;
    BucketheadZombieStatus m_status;
};

#endif // BUCKETHEADZOMBIE_H
