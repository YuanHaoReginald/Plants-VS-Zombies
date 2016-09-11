#include "normalzombie.h"
#include "globalmanager.h"
#include <QTimer>

NormalZombie::NormalZombie(int RowVal, int idVal) 
{
    Row = RowVal;
    id = idVal;
    ThisZombieType = ZombieType::NormalZombie;
    Blood = 10;
    Speed = 80;
    Width = 166;
    Height = 144;
    PosX = 900;
    PosY = GlobalManager::PosY[Row] - Height;
    ZombieLabel = new QLabel(GlobalManager::CurrentWidget);
    ZombieLabel->setMouseTracking(true);
    ZombieMovie = new QMovie(":/zombie/res/images/zombie/Zombie/Zombie.gif");
    ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
    ZombieLabel->setMovie(ZombieMovie);
    ZombieLabel->resize(ForScale(166), ForScale(144));
    ZombieLabel->move(ForScale(PosX), ForScale(PosY));
    ZombieMovie->start();
    ZombieLabel->show();
    ZombieLabel->raise();
    CurrentStatus = NormalZombieStatus::Normal;
    
    HeadLabel = nullptr;
    HeadMovie = nullptr;
    BodyLabel = nullptr;
    BodyMovie = nullptr;
}

NormalZombie::~NormalZombie()
{
    delete HeadLabel;
    delete HeadMovie;
    delete BodyLabel;
    delete BodyMovie;
}

void NormalZombie::getAttack()
{
    Blood--;
    if(Blood == 0)
    {
        delete ZombieLabel;
        ZombieLabel = nullptr;
        delete ZombieMovie;
        ZombieMovie = nullptr;
        
        HeadLabel = new QLabel(GlobalManager::CurrentWidget);
        HeadLabel->setMouseTracking(true);
        HeadMovie = new QMovie(":/zombie/res/images/zombie/Zombie/ZombieHead.gif");
        HeadMovie->setScaledSize(QSize(ForScale(150), ForScale(186)));
        HeadLabel->setMovie(HeadMovie);
        HeadLabel->resize(ForScale(150), ForScale(186));
        HeadLabel->move(ForScale(PosX + 80), ForScale(PosY - 42));
        
        BodyLabel = new QLabel(GlobalManager::CurrentWidget);
        BodyLabel->setMouseTracking(true);
        BodyMovie = new QMovie(":/zombie/res/images/zombie/Zombie/ZombieDie.gif");
        BodyMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
        BodyLabel->setMovie(BodyMovie);
        BodyLabel->resize(ForScale(166), ForScale(144));
        BodyLabel->move(ForScale(PosX), ForScale(PosY));
        
        HeadMovie->start();
        BodyMovie->start();
        HeadLabel->show();
        HeadLabel->raise();
        BodyLabel->show();
        BodyLabel->raise();
        
        QTimer::singleShot(560, this, SLOT(DeleteHead()));
        QTimer::singleShot(2000, this, SLOT(DeleteBody()));
        CurrentStatus = NormalZombieStatus::Die;
    }
}

void NormalZombie::SwitchStatus()
{    
    if(CurrentStatus == NormalZombieStatus::Normal)
    {
        delete ZombieMovie;
        ZombieMovie = new QMovie(":/zombie/res/images/zombie/Zombie/ZombieAttack.gif");
        ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
        ZombieLabel->setMovie(ZombieMovie);
        ZombieMovie->start();
        CurrentStatus = NormalZombieStatus::Eating;
    }
    else if(CurrentStatus == NormalZombieStatus::Eating)
    {
        delete ZombieMovie;
        ZombieMovie = new QMovie(":/zombie/res/images/zombie/Zombie/Zombie.gif");
        ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
        ZombieLabel->setMovie(ZombieMovie);
        ZombieMovie->start();
        CurrentStatus = NormalZombieStatus::Normal;
    }
}

void NormalZombie::ZombieMove()
{
    if(CurrentStatus == NormalZombieStatus::Normal)
    {
        PosX--;
        ZombieLabel->move(ForScale(PosX), ForScale(PosY));
    }
}

void NormalZombie::DeleteHead()
{
    delete HeadLabel;
    delete HeadMovie;
    HeadLabel = nullptr;
    HeadMovie = nullptr;
}

void NormalZombie::DeleteBody()
{
    delete BodyLabel;
    delete BodyMovie;
    BodyLabel = nullptr;
    BodyMovie = nullptr;
    emit die(this, id);
}
