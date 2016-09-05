#include "sun.h"
#include <QMovie>
#include <QSize>
#include <QTimer>
#include "globalmanager.h"
#include <QDebug>

Sun::Sun(int FallSiteX, QObject *parent, int TempType) 
    : QObject(parent), m_Type(TempType)
{
    m_Mode = Mode::Fall;
    FlowerTimer = nullptr;
    DelayTimer = nullptr;
    BackTimer = nullptr;
    SunGif = new QMovie(":/surface/res/images/surface/Sun.gif");
    SunGif->setScaledSize(QSize(ForScale(70), ForScale(70)));
    SunLabel = new Label(GlobalManager::CurrentWidget);
    SunLabel->setMovie(SunGif);
    DelayTimer = new QTimer;
    DelayTimer->setInterval(8000);
    connect(DelayTimer, SIGNAL(timeout()), this, SLOT(DelayDie()));
    SunGif->start();
    connect(SunLabel, SIGNAL(clicked()), this, SLOT(GetSun()));
    
    if(FallSiteX <= 140)
        FallSiteX = 140;
    else if(FallSiteX >= 790)
        FallSiteX = 790;
    posX = FallSiteX;
    posY = 84;
    SunLabel->setGeometry(ForScale(posX), ForScale(posY), ForScale(70), ForScale(70));
    FallTimer = new QTimer;
    FallTimer->setInterval(15);
    connect(FallTimer, SIGNAL(timeout()), this, SLOT(FallEvent()));
    FallTimer->start();
}

Sun::Sun(int FlowerRow, int FlowerCulumn, QObject *parent, int TempType)
    : QObject(parent), m_Type(TempType)
{  
    m_Mode = Mode::Flower;
    FallTimer = nullptr;
    DelayTimer = nullptr;
    BackTimer = nullptr;
    SunGif = new QMovie(":/surface/res/images/surface/Sun.gif");
    SunGif->setScaledSize(QSize(ForScale(70), ForScale(70)));
    SunLabel = new Label(GlobalManager::CurrentWidget);
    SunLabel->setMovie(SunGif);
    DelayTimer = new QTimer;
    DelayTimer->setInterval(8000);
    connect(DelayTimer, SIGNAL(timeout()), this, SLOT(DelayDie()));    
    connect(SunLabel, SIGNAL(clicked()), this, SLOT(GetSun()));
    
    if(FlowerRow <= 0)
        FlowerRow = 0;
    else if(FlowerRow >= 4)
        FlowerRow = 4;
    if(FlowerCulumn <= 0)
        FlowerCulumn = 0;
    else if(FlowerCulumn >= 8)
        FlowerCulumn = 8;
    posX = GlobalManager::posX[FlowerCulumn] + 5;
    posY = GlobalManager::posY[FlowerRow];
    SunLabel->setGeometry(ForScale(posX), ForScale(posY), ForScale(70), ForScale(70));
    FlowerTimer = new QTimer;
    FlowerTimer ->setInterval(5);
    connect(FlowerTimer, SIGNAL(timeout()), this, SLOT(FlowerFall()));
    TimeUsed = 0;
    FlowerTimer->start();
}

Sun::~Sun()
{
    delete SunGif;
    delete SunLabel;
    delete FallTimer;
    delete DelayTimer;
    delete BackTimer;
    delete FlowerTimer;
}

int Sun::getType()
{
    return m_Type;
}

Label* Sun::getLabel()
{
    return SunLabel;
}


void Sun::FallEvent()
{
    posY += 1;
    SunLabel->setGeometry(ForScale(posX), ForScale(posY), ForScale(70), ForScale(70));
    if(posY == 530)
    {
        FallTimer->stop();
        DelayTimer->start();
        //qDebug() << "   "  << DelayTimer->remainingTime() << "\n";
    }
}

void Sun::FlowerFall()
{
    TimeUsed += 5;
    SunLabel->setGeometry(ForScale(posX - 0.07 * TimeUsed),ForScale(1.0 * 21 * TimeUsed * TimeUsed / 125000
                                                                    - 1.0 * 3 * TimeUsed / 125 + posY) 
                          , ForScale(70), ForScale(70));
    if(TimeUsed == 500)
    {
        FlowerTimer->stop();
        posX -= 35;
        posY += 30;
        DelayTimer->start();
    }
}

void Sun::DelayDie()
{
    emit die(this);
}

void Sun::GetSun()
{
    //emit GetSunUp(m_Type);
    if(FallTimer->isActive())
        FallTimer->stop();
    else if(DelayTimer->isActive())
        DelayTimer->stop();
    else if(FlowerTimer->isActive())
        FlowerTimer->stop();
    BackTimer = new QTimer;
    BackTimer->setInterval(5);
    TimeUsed = 0;
    BackTimer->start();
    connect(BackTimer, SIGNAL(timeout()), this, SLOT(SunBack()));
}

void Sun::SunBack()
{
    TimeUsed += 5;
    SunLabel->setGeometry(ForScale(posX + (posX - 15) * 1.0 * TimeUsed * TimeUsed / 250000 
                                   - (posX - 15) * 1.0 * TimeUsed / 250),
                          ForScale(posY + (posY - 9) * 1.0 * TimeUsed * TimeUsed / 250000 
                                   - (posY - 9) * 1.0 * TimeUsed / 250),
                          ForScale(70), ForScale(70));
    //qDebug() << this << "    " << TimeUsed << "     " << SunLabel->x() << "     " << SunLabel->y() << "\n";
    if(TimeUsed == 500)
    {
        BackTimer->stop();
        emit GetSunUp(m_Type);
        emit die(this);
    }
}

void Sun::Pause()
{
    switch (CurrentStatus) {
    case SunStatus::Fall:
        if(m_Mode == Mode::Fall)
            FallTimer->stop();
        else if(m_Mode == Mode::Fall)
            FlowerTimer->stop();
        break;
    case SunStatus::Delay:
        LeftMSec = DelayTimer->remainingTime(); 
        DelayTimer->stop();
        break;
    case SunStatus::Back:
        BackTimer->stop();
        break;
    default:
        break;
    }
}

void Sun::Restart()
{
    switch (CurrentStatus) {
    case SunStatus::Fall:
        if(m_Mode == Mode::Fall)
            FallTimer->start();
        else if(m_Mode == Mode::Fall)
            FlowerTimer->start();
        break;
    case SunStatus::Delay:
        DelayTimer->setInterval(LeftMSec);
        DelayTimer->start();
        break;
    case SunStatus::Back:
        BackTimer->start();
        break;
    default:
        break;
    }
}

void Sun::RaiseSun()
{
    SunLabel->raise();
}

void Sun::DeleteThis()
{
    emit die(this);
}
