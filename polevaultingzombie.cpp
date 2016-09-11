#include "polevaultingzombie.h"
#include "globalmanager.h"
#include <QTimer>

PoleVaultingZombie::PoleVaultingZombie(int RowVal, int idVal)
{
    Row = RowVal;
    id = idVal;
    ThisZombieType = ZombieType::PoleVaultingZombie;
    Blood = 17;
    Speed = 50;
    Width = 348;
    Height = 218;
    PosX = 900;
    PosY = GlobalManager::PosY[Row] - Height;
    ZombieLabel = new QLabel(GlobalManager::CurrentWidget);
    ZombieLabel->setMouseTracking(true);
    ZombieMovie = new QMovie(":/zombie/res/images/zombie/PoleVaultingZombie/PoleVaultingZombie.gif");
    ZombieMovie->setScaledSize(QSize(ForScale(348), ForScale(218)));
    ZombieLabel->setMovie(ZombieMovie);
    ZombieLabel->resize(ForScale(348), ForScale(218));
    ZombieLabel->move(ForScale(PosX), ForScale(PosY));
    ZombieMovie->start();
    ZombieLabel->show();
    ZombieLabel->raise();
    CurrentStatus = PoleVaultingZombieStatus::Pole;
    
    HeadLabel = nullptr;
    HeadMovie = nullptr;
    BodyLabel = nullptr;
    BodyMovie = nullptr;
}

PoleVaultingZombie::~PoleVaultingZombie()
{
    delete HeadLabel;
    delete HeadMovie;
    delete BodyLabel;
    delete BodyMovie;
}

void PoleVaultingZombie::getAttack()
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
        HeadMovie = new QMovie(":/zombie/res/images/zombie/PoleVaultingZombie/PoleVaultingZombieHead.gif");
        HeadMovie->setScaledSize(QSize(ForScale(348), ForScale(218)));
        HeadLabel->setMovie(HeadMovie);
        HeadLabel->resize(ForScale(348), ForScale(218));
        HeadLabel->move(ForScale(PosX - 27), ForScale(PosY));
        
        BodyLabel = new QLabel(GlobalManager::CurrentWidget);
        BodyLabel->setMouseTracking(true);
        BodyMovie = new QMovie(":/zombie/res/images/zombie/PoleVaultingZombie/PoleVaultingZombieHead.gif");
        BodyMovie->setScaledSize(QSize(ForScale(348), ForScale(218)));
        BodyLabel->setMovie(BodyMovie);
        BodyLabel->resize(ForScale(348), ForScale(218));
        BodyLabel->move(ForScale(PosX), ForScale(PosY));
        
        HeadMovie->start();
        BodyMovie->start();
        HeadLabel->show();
        HeadLabel->raise();
        BodyLabel->show();
        BodyLabel->raise();
        
        QTimer::singleShot(560, this, SLOT(DeleteHead()));
        QTimer::singleShot(2000, this, SLOT(DeleteBody()));
        CurrentStatus = PoleVaultingZombieStatus::Die;
    }
}

void PoleVaultingZombie::SwitchStatus()
{    
    if(CurrentStatus == PoleVaultingZombieStatus::Normal)
    {
        delete ZombieMovie;
        ZombieMovie = new QMovie(":/zombie/res/images/zombie/PoleVaultingZombie/PoleVaultingZombieAttack.gif");
        ZombieMovie->setScaledSize(QSize(ForScale(348), ForScale(218)));
        ZombieLabel->setMovie(ZombieMovie);
        ZombieMovie->start();
        CurrentStatus = PoleVaultingZombieStatus::Eating;
    }
    else if(CurrentStatus == PoleVaultingZombieStatus::Eating)
    {
        delete ZombieMovie;
        ZombieMovie = new QMovie(":/zombie/res/images/zombie/PoleVaultingZombie/PoleVaultingZombieWalk.gif");
        ZombieMovie->setScaledSize(QSize(ForScale(348), ForScale(218)));
        ZombieLabel->setMovie(ZombieMovie);
        ZombieMovie->start();
        CurrentStatus = PoleVaultingZombieStatus::Normal;
    }
}

void PoleVaultingZombie::ZombieMove()
{
    if(CurrentStatus == PoleVaultingZombieStatus::Normal || CurrentStatus == PoleVaultingZombieStatus::Pole)
    {
        PosX--;
        ZombieLabel->move(ForScale(PosX), ForScale(PosY));
    }
}

void PoleVaultingZombie::Jump()
{
    if(CurrentStatus == PoleVaultingZombieStatus::Pole)
    {
        CurrentStatus = PoleVaultingZombieStatus::Jump;
        delete ZombieMovie;
        ZombieMovie = new QMovie(":/zombie/res/images/zombie/PoleVaultingZombie/PoleVaultingZombieJump.gif");
        ZombieMovie->setScaledSize(QSize(ForScale(348), ForScale(218)));
        ZombieLabel->setMovie(ZombieMovie);
        ZombieMovie->start();
        QTimer::singleShot(1000, this, SLOT(Jump2()));
    }
}

void PoleVaultingZombie::DeleteHead()
{
    delete HeadLabel;
    delete HeadMovie;
    HeadLabel = nullptr;
    HeadMovie = nullptr;
}

void PoleVaultingZombie::DeleteBody()
{
    delete BodyLabel;
    delete BodyMovie;
    BodyLabel = nullptr;
    BodyMovie = nullptr;
    emit die(this, id);
}

void PoleVaultingZombie::Jump2()
{
    delete ZombieMovie;
    ZombieMovie = new QMovie(":/zombie/res/images/zombie/PoleVaultingZombie/PoleVaultingZombieJump2.gif");
    ZombieMovie->setScaledSize(QSize(ForScale(348), ForScale(218)));
    ZombieLabel->setMovie(ZombieMovie);
    ZombieMovie->start();
    PosX -= 124;
    ZombieLabel->move(ForScale(PosX), ForScale(PosY));
    QTimer::singleShot(700, this, SLOT(Jump3()));
}

void PoleVaultingZombie::Jump3()
{
    delete ZombieMovie;
    ZombieMovie = new QMovie(":/zombie/res/images/zombie/PoleVaultingZombie/PoleVaultingZombieWalk.gif");
    ZombieMovie->setScaledSize(QSize(ForScale(349), ForScale(218)));
    ZombieLabel->setMovie(ZombieMovie);
    ZombieMovie->start();
    Speed = 100;
    CurrentStatus = PoleVaultingZombieStatus::Normal;
}
