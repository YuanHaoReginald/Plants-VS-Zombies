#include "sunmanager.h"
#include "sun.h"
#include "globalmanager.h"
#include <cstdlib>
#include <QLabel>
#include <QTime>

SunManager::SunManager(QObject *parent) : QObject(parent)
{
    MainManagerTimer = new QTimer;
    connect(MainManagerTimer, SIGNAL(timeout()), this, SLOT(GenerateSun()));
    showSunNum = new QLabel(GlobalManager::CurrentWidget);
    showSunNum->setGeometry(ForScale(26), ForScale(59), ForScale(54), ForScale(21));
    showSunNum->setAlignment(Qt::AlignCenter);
    showSunNum->setText(QString::number(GlobalManager::NumberOfSun));
    showSunNum->show();
}

SunManager::~SunManager()
{
    emit DeleteAllSun();
    delete MainManagerTimer;
    delete showSunNum;
}

void SunManager::Start()
{
    isPause = true;
    MainManagerTimer->setInterval(2000);
    MainManagerTimer->start();
}

void SunManager::Pause()
{
    leftmsec = MainManagerTimer->remainingTime();
    MainManagerTimer->stop();
    emit PauseAllSun();
}

void SunManager::Restart()
{
    isPause = true;
    MainManagerTimer->setInterval(leftmsec);
    MainManagerTimer->start();
    emit RestartAllSun();
}

void SunManager::GenerateSun()
{
    if(isPause)
    {
        MainManagerTimer->stop();
        MainManagerTimer->setInterval(6000);
        isPause = false;
        MainManagerTimer->start();
    }
    srand(QTime::currentTime().msecsSinceStartOfDay());
    int TargetSite = rand() % 650 + 140;
    Sun *temp = new Sun(TargetSite, this);
    temp->getLabel()->show();
    connect(this, SIGNAL(UpAllSun()), temp, SLOT(RaiseSun()));
    connect(this, SIGNAL(PauseAllSun()), temp, SLOT(Pause()));
    connect(this, SIGNAL(RestartAllSun()), temp, SLOT(Restart()));
    connect(temp, SIGNAL(GetSunUp(int)), this, SLOT(AddSunNumber(int)));
    connect(temp, SIGNAL(die(Sun*)), this, SLOT(DeleteSun(Sun*)));
    connect(this, SIGNAL(DeleteAllSun()), temp, SLOT(DeleteThis()));
}

void SunManager::FlowerSun(int Row, int Culumn)
{
    Sun *temp = new Sun(Row, Culumn, this);
    temp->getLabel()->show();
    connect(this, SIGNAL(UpAllSun()), temp, SLOT(RaiseSun()));
    connect(this, SIGNAL(PauseAllSun()), temp, SLOT(Pause()));
    connect(this, SIGNAL(RestartAllSun()), temp, SLOT(Restart()));
    connect(temp, SIGNAL(GetSunUp(int)), this, SLOT(AddSunNumber(int)));
    connect(temp, SIGNAL(die(Sun*)), this, SLOT(DeleteSun(Sun*)));
    connect(this, SIGNAL(DeleteAllSun()), temp, SLOT(DeleteThis()));    
}


void SunManager::AddSunNumber(int nowType)
{
    GlobalManager::NumberOfSun += nowType;
    emit SunNumberUpdate();
    showSunNum->setText(QString::number(GlobalManager::NumberOfSun));    
}

void SunManager::DeleteSun(Sun * Point)
{
    delete Point;
}

void SunManager::MinusSunNumber(int num)
{
    GlobalManager::NumberOfSun -= num;
    emit SunNumberUpdate();
    showSunNum->setText(QString::number(GlobalManager::NumberOfSun));    
}
