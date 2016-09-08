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
    
    enum class NormalZombieStatus {Normal, Eating, die};
    
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
    NormalZombieStatus m_status;
};

#endif // NORMALZOMBIES_H
