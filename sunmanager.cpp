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
    ShowSunNumberLabel = new QLabel(GlobalManager::CurrentWidget);
    ShowSunNumberLabel->setMouseTracking(true);
    ShowSunNumberLabel->setGeometry(ForScale(26), ForScale(59), ForScale(54), ForScale(21));
    ShowSunNumberLabel->setAlignment(Qt::AlignCenter);
    ShowSunNumberLabel->setText(QString::number(GlobalManager::SunNumber));
    ShowSunNumberLabel->show();
}

SunManager::~SunManager()
{
    emit DeleteAllSun();
    delete MainManagerTimer;
    delete ShowSunNumberLabel;
}

void SunManager::Start()
{
    MainManagerTimer->setInterval(6000);
    QTimer::singleShot(2000, this, SLOT(GenerateSun()));
}

void SunManager::GenerateSun()
{
    if(!(MainManagerTimer->isActive()))
    {
        MainManagerTimer->start();
    }
    srand(QTime::currentTime().msecsSinceStartOfDay());
    int TargetSite = rand() % 650 + 140;
    Sun *temp = new Sun(TargetSite, this);
    temp->SunLabel->show();
    connect(this, SIGNAL(UpAllSun()), temp, SLOT(RaiseSun()));
    connect(temp, SIGNAL(GetSunUp(int)), this, SLOT(AddSunNumber(int)));
    connect(temp, SIGNAL(die(Sun*)), this, SLOT(DeleteSun(Sun*)));
    connect(this, SIGNAL(DeleteAllSun()), temp, SLOT(DeleteThis()));
}

void SunManager::FlowerSun(int Row, int Culumn)
{
    Sun *temp = new Sun(Row, Culumn, this);
    temp->SunLabel->show();
    temp->SunLabel->raise();
    connect(this, SIGNAL(UpAllSun()), temp, SLOT(RaiseSun()));
    connect(temp, SIGNAL(GetSunUp(int)), this, SLOT(AddSunNumber(int)));
    connect(temp, SIGNAL(die(Sun*)), this, SLOT(DeleteSun(Sun*)));
    connect(this, SIGNAL(DeleteAllSun()), temp, SLOT(DeleteThis())); 
}


void SunManager::AddSunNumber(int nowType)
{
    GlobalManager::SunNumber += nowType;
    emit SunNumberUpdate();
    ShowSunNumberLabel->setText(QString::number(GlobalManager::SunNumber));    
}

void SunManager::DeleteSun(Sun * Point)
{
    delete Point;
}

void SunManager::MinusSunNumber(int num)
{
    GlobalManager::SunNumber -= num;
    emit SunNumberUpdate();
    ShowSunNumberLabel->setText(QString::number(GlobalManager::SunNumber));    
}
