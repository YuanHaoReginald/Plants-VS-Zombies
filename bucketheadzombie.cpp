#include "bucketheadzombie.h"
#include "globalmanager.h"
#include <QTimer>

BucketheadZombie::BucketheadZombie(int RowVal, int idVal)
{
    Row = RowVal;
    id = idVal;
    ThisZombieType = ZombieType::BucketheadZombie;
    Blood = 65;
    Speed = 80;
    Width = 166;
    Height = 144;
    PosX = 900;
    PosY = GlobalManager::PosY[Row] - Height;
    ZombieLabel = new QLabel(GlobalManager::CurrentWidget);
    ZombieLabel->setMouseTracking(true);
    ZombieMovie = new QMovie(":/zombie/res/images/zombie/BucketheadZombie/BucketheadZombie.gif");
    ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
    ZombieLabel->setMovie(ZombieMovie);
    ZombieLabel->resize(ForScale(166), ForScale(144));
    ZombieLabel->move(ForScale(PosX), ForScale(PosY));
    ZombieMovie->start();
    ZombieLabel->show();
    ZombieLabel->raise();
    CurrentStatus = BucketheadZombieStatus::HeadNormal;
    
    HeadLabel = nullptr;
    HeadMovie = nullptr;
    BodyLabel = nullptr;
    BodyMovie = nullptr;
}

BucketheadZombie::~BucketheadZombie()
{
    delete HeadLabel;
    delete HeadMovie;
    delete BodyLabel;
    delete BodyMovie;
}

void BucketheadZombie::getAttack()
{
    Blood--;
    if(Blood == 10)
    {
        if(CurrentStatus == BucketheadZombieStatus::HeadNormal)
        {
            delete ZombieMovie;
            ZombieMovie = new QMovie(":/zombie/res/images/zombie/Zombie/Zombie.gif");
            ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
            ZombieLabel->setMovie(ZombieMovie);
            ZombieMovie->start();
            CurrentStatus = BucketheadZombieStatus::Normal;            
        }
        else
        {
            delete ZombieMovie;
            ZombieMovie = new QMovie(":/zombie/res/images/zombie/Zombie/ZombieAttack.gif");
            ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
            ZombieLabel->setMovie(ZombieMovie);
            ZombieMovie->start();
            CurrentStatus = BucketheadZombieStatus::Eating;
        }
    }
    else if(Blood == 0)
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
        HeadLabel->move(ForScale(PosX), ForScale(PosY - 42));
        
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
        CurrentStatus = BucketheadZombieStatus::Die;
    }
}

void BucketheadZombie::SwitchStatus()
{    
    if(CurrentStatus == BucketheadZombieStatus::HeadNormal)
    {
        delete ZombieMovie;
        ZombieMovie = new QMovie(":/zombie/res/images/zombie/BucketheadZombie/BucketheadZombieAttack.gif");
        ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
        ZombieLabel->setMovie(ZombieMovie);
        ZombieMovie->start();
        CurrentStatus = BucketheadZombieStatus::HeadEating;
    }
    else if(CurrentStatus == BucketheadZombieStatus::HeadEating)
    {
        delete ZombieMovie;
        ZombieMovie = new QMovie(":/zombie/res/images/zombie/BucketheadZombie/BucketheadZombie.gif");
        ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
        ZombieLabel->setMovie(ZombieMovie);
        ZombieMovie->start();
        CurrentStatus = BucketheadZombieStatus::HeadNormal;
    }
    else if(CurrentStatus == BucketheadZombieStatus::Normal)
    {
        delete ZombieMovie;
        ZombieMovie = new QMovie(":/zombie/res/images/zombie/Zombie/ZombieAttack.gif");
        ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
        ZombieLabel->setMovie(ZombieMovie);
        ZombieMovie->start();
        CurrentStatus = BucketheadZombieStatus::Eating;
    }
    else if(CurrentStatus == BucketheadZombieStatus::Eating)
    {
        delete ZombieMovie;
        ZombieMovie = new QMovie(":/zombie/res/images/zombie/Zombie/Zombie.gif");
        ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
        ZombieLabel->setMovie(ZombieMovie);
        ZombieMovie->start();
        CurrentStatus = BucketheadZombieStatus::Normal;
    }
}

void BucketheadZombie::ZombieMove()
{
    if(CurrentStatus == BucketheadZombieStatus::Normal || CurrentStatus == BucketheadZombieStatus::HeadNormal)
    {
        PosX--;
        ZombieLabel->move(ForScale(PosX), ForScale(PosY));
    }
}

void BucketheadZombie::DeleteHead()
{
    delete HeadLabel;
    delete HeadMovie;
    HeadLabel = nullptr;
    HeadMovie = nullptr;
}

void BucketheadZombie::DeleteBody()
{
    delete BodyLabel;
    delete BodyMovie;
    BodyLabel = nullptr;
    BodyMovie = nullptr;
    emit die(this, id);
}
