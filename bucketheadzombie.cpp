#include "bucketheadzombie.h"
#include "globalmanager.h"
#include <QTimer>

BucketheadZombie::BucketheadZombie(int RowVal, int idVal)
{
    Row = RowVal;
    id = idVal;
    m_Type = ZombieType::BucketheadZombie;
    blood = 65;
    speed = 150;
    width = 166;
    height = 144;
    PosX = 900;
    PosY = GlobalManager::posY[Row] - height;
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
    m_status = BucketheadZombieStatus::HeadNormal;
    
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

int BucketheadZombie::getStatus()
{
    return static_cast<int>(m_status);
}

void BucketheadZombie::getAttack()
{
    blood--;
    if(blood == 10)
    {
        if(m_status == BucketheadZombieStatus::HeadNormal)
        {
            delete ZombieMovie;
            ZombieMovie = new QMovie(":/zombie/res/images/zombie/Zombie/Zombie.gif");
            ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
            ZombieLabel->setMovie(ZombieMovie);
            ZombieMovie->start();
            m_status = BucketheadZombieStatus::Normal;            
        }
        else
        {
            delete ZombieMovie;
            ZombieMovie = new QMovie(":/zombie/res/images/zombie/Zombie/ZombieAttack.gif");
            ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
            ZombieLabel->setMovie(ZombieMovie);
            ZombieMovie->start();
            m_status = BucketheadZombieStatus::Eating;
        }
    }
    else if(blood == 0)
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
        m_status = BucketheadZombieStatus::Die;
    }
}

void BucketheadZombie::SwitchStatus()
{    
    if(m_status == BucketheadZombieStatus::HeadNormal)
    {
        delete ZombieMovie;
        ZombieMovie = new QMovie(":/zombie/res/images/zombie/BucketheadZombie/BucketheadZombieAttack.gif");
        ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
        ZombieLabel->setMovie(ZombieMovie);
        ZombieMovie->start();
        m_status = BucketheadZombieStatus::HeadEating;
    }
    else if(m_status == BucketheadZombieStatus::HeadEating)
    {
        delete ZombieMovie;
        ZombieMovie = new QMovie(":/zombie/res/images/zombie/BucketheadZombie/BucketheadZombie.gif");
        ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
        ZombieLabel->setMovie(ZombieMovie);
        ZombieMovie->start();
        m_status = BucketheadZombieStatus::HeadNormal;
    }
    else if(m_status == BucketheadZombieStatus::Normal)
    {
        delete ZombieMovie;
        ZombieMovie = new QMovie(":/zombie/res/images/zombie/Zombie/ZombieAttack.gif");
        ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
        ZombieLabel->setMovie(ZombieMovie);
        ZombieMovie->start();
        m_status = BucketheadZombieStatus::Eating;
    }
    else if(m_status == BucketheadZombieStatus::Eating)
    {
        delete ZombieMovie;
        ZombieMovie = new QMovie(":/zombie/res/images/zombie/Zombie/Zombie.gif");
        ZombieMovie->setScaledSize(QSize(ForScale(166), ForScale(144)));
        ZombieLabel->setMovie(ZombieMovie);
        ZombieMovie->start();
        m_status = BucketheadZombieStatus::Normal;
    }
}

void BucketheadZombie::ZombieMove()
{
    if(m_status == BucketheadZombieStatus::Normal || m_status == BucketheadZombieStatus::HeadNormal)
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
