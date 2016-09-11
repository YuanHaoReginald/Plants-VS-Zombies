#include "sun.h"
#include <QMovie>
#include <QSize>
#include <QTimer>
#include "globalmanager.h"

Sun::Sun(int FallSiteX, QObject *parent, int TempType) 
    : QObject(parent), SunType(TempType)
{
    SunMode = Mode::Fall;
    FlowerTimer = new QTimer;
    BackTimer = new QTimer;
    
    SunGif = new QMovie(":/surface/res/images/surface/Sun.gif");
    SunGif->setScaledSize(QSize(ForScale(70), ForScale(70)));
    SunLabel = new Label(GlobalManager::CurrentWidget);
    SunLabel->setMouseTracking(true);
    SunLabel->setMovie(SunGif);
    SunGif->start();
    connect(SunLabel, SIGNAL(clicked()), this, SLOT(GetSun()));
    
    DelayTimer = new QTimer;
    DelayTimer->setInterval(8000);
    connect(DelayTimer, SIGNAL(timeout()), this, SLOT(DelayDie()));
    
    if(FallSiteX <= 140)
        FallSiteX = 140;
    else if(FallSiteX >= 790)
        FallSiteX = 790;
    PosX = FallSiteX;
    PosY = 84;
    SunLabel->setGeometry(ForScale(PosX), ForScale(PosY), ForScale(70), ForScale(70));
    FallTimer = new QTimer;
    FallTimer->setInterval(15);
    connect(FallTimer, SIGNAL(timeout()), this, SLOT(SkyFall()));
    FallTimer->start();
}

Sun::Sun(int FlowerRow, int FlowerColumn, QObject *parent, int TempType)
    : QObject(parent), SunType(TempType)
{  
    SunMode = Mode::Flower;
    FallTimer = new QTimer;
    BackTimer = new QTimer;
    
    SunGif = new QMovie(":/surface/res/images/surface/Sun.gif");
    SunGif->setScaledSize(QSize(ForScale(70), ForScale(70)));
    SunLabel = new Label(GlobalManager::CurrentWidget);
    SunLabel->setMouseTracking(true);
    SunLabel->setMovie(SunGif);
    SunGif->start();
    connect(SunLabel, SIGNAL(clicked()), this, SLOT(GetSun()));
    
    DelayTimer = new QTimer;
    DelayTimer->setInterval(8000);
    connect(DelayTimer, SIGNAL(timeout()), this, SLOT(DelayDie()));  
    
    if(FlowerRow <= 1)
        FlowerRow = 1;
    else if(FlowerRow >= 5)
        FlowerRow = 5;
    if(FlowerColumn <= 1)
        FlowerColumn = 1;
    else if(FlowerColumn >= 9)
        FlowerColumn = 9;
    PosX = GlobalManager::PosX[FlowerColumn - 1] + 5;
    PosY = GlobalManager::PosY[FlowerRow - 1];
    SunLabel->setGeometry(ForScale(PosX), ForScale(PosY), ForScale(70), ForScale(70));
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

void Sun::SkyFall()
{
    PosY += 1;
    SunLabel->setGeometry(ForScale(PosX), ForScale(PosY), ForScale(70), ForScale(70));
    if(PosY == 530)
    {
        FallTimer->stop();
        DelayTimer->start();
    }
}

void Sun::FlowerFall()
{
    TimeUsed += 5;
    SunLabel->move(ForScale(PosX - 0.07 * TimeUsed),ForScale(1.0 * 21 * TimeUsed * TimeUsed / 125000
                                                             - 1.0 * 3 * TimeUsed / 125 + PosY));
    if(TimeUsed == 500)
    {
        FlowerTimer->stop();
        PosX -= 35;
        PosY += 30;
        DelayTimer->start();
    }
}

void Sun::DelayDie()
{
    emit die(this);
}

void Sun::GetSun()
{
    disconnect(SunLabel, SIGNAL(clicked()), this, SLOT(GetSun()));    
    if(FallTimer->isActive())
        FallTimer->stop();
    if(DelayTimer->isActive())
        DelayTimer->stop();
    if(FlowerTimer->isActive())
        FlowerTimer->stop();
    BackTimer->setInterval(5);
    TimeUsed = 0;
    BackTimer->start();
    connect(BackTimer, SIGNAL(timeout()), this, SLOT(SunBack()));
}

void Sun::SunBack()
{
    TimeUsed += 5;
    SunLabel->move(ForScale(PosX + (PosX - 15) * 1.0 * TimeUsed * TimeUsed / 250000 
                            - (PosX - 15) * 1.0 * TimeUsed / 250),
                   ForScale(PosY + (PosY - 9) * 1.0 * TimeUsed * TimeUsed / 250000 
                            - (PosY - 9) * 1.0 * TimeUsed / 250));
    if(TimeUsed == 500)
    {
        BackTimer->stop();
        emit GetSunUp(SunType);
        emit die(this);
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
