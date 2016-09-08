#include "normalzombie.h"
#include "globalmanager.h"
#include <QTimer>

NormalZombie::NormalZombie(int RowVal, int isVal) : Row(RowVal), id(idVal)
{
    m_Type = ZombieType::NormalZombie;
    blood = 10;
    speed = 150;
    width = 166;
    height = 144;
    PosX = 900;
    PosY = GlobalManager::posY[Row] - height;
    ZombieLabel = new QLabel(GlobalManager::CurrentWidget);
    ZombieMovie = new QMovie(":/zombie/res/images/zombie/Zombie/Zombie.gif");
    ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
    ZombieLabel->setMovie(ZombieMovie);
    ZombieLabel->resize(ForScale(166), ForScale(144));
    ZombieLabel->move(ForScale(PosX), ForScale(PosY));
    ZombieMovie->start();
    ZombieLabel->show();
    ZombieLabel->raise();
    m_status = NormalZombieStatus::Normal;
    
    HeadLabel = nullptr;
    HeadMovie = nullptr;
    BodyLabel = nullptr;
    BodyMovie = nullptr;
}

int NormalZombie::getType()
{
    return static_cast<int>(m_status);
}

void NormalZombie::getAttack()
{
    blood--;
    if(blood == 0)
    {
        delete ZombieLabel;
        ZombieLabel = nullptr;
        delete ZombieMovie;
        ZombieMovie = nullptr;
        
        HeadLabel = new QLabel(GlobalManager::CurrentWidget);
        HeadMovie = new QMovie(":/zombie/res/images/zombie/Zombie/ZombieHead.gif");
        HeadMovie->setScaledSize(QSize(ForScale(150), ForScale(186)));
        HeadLabel->setMovie(HeadMovie);
        HeadLabel->resize(ForScale(150), ForScale(186));
        HeadLabel->move(ForScale(PosX), ForScale(PosY - 42));
        
        BodyLabel = new QLabel(GlobalManager::CurrentWidget);
        BodyMovie = new QPixmap(":/zombie/res/images/zombie/Zombie/ZombieDie.gif");
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
    }
}

void NormalZombie::SwitchStatus()
{    
    if(m_status == NormalZombieStatus::Normal)
    {
        delete ZombieMovie;
        ZombieMovie = new QMovie(":/zombie/res/images/zombie/Zombie/ZombieAttack.gif");
        ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
        ZombieLabel->setMovie(ZombieMovie);
        ZombieMovie->start();
        m_status = NormalZombieStatus::Eating;
    }
    else if(m_status == NormalZombieStatus::Eating)
    {
        delete ZombieMovie;
        ZombieMovie = new QMovie(":/zombie/res/images/zombie/Zombie/Zombie.gif");
        ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
        ZombieLabel->setMovie(ZombieMovie);
        ZombieMovie->start();
        m_status = NormalZombieStatus::Normal;
    }
}

void NormalZombie::ZombieMove()
{
    if(m_status = NormalZombieStatus::Normal)
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
    emit die(this);
}
