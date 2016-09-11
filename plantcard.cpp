#include "plantcard.h"
#include "globalmanager.h"
#include <QPixmap>

PlantCard::PlantCard(PlantType TypeVal, int CardID, QObject *parent) : QObject(parent), CardType(TypeVal)
{
    switch(TypeVal)
    {
    case PlantType::SunFlower:
        SunCost = 50;
        FreezeMsec = 7500;
        NormalPixmap = new QPixmap(":/card/res/images/card/Sunflower.png");
        break;
    case PlantType::WallNut:
        SunCost = 50;
        FreezeMsec = 30000;
        NormalPixmap = new QPixmap(":/card/res/images/card/WallNut.png");
        break;
    case PlantType::Peashooter:
        SunCost = 100;
        FreezeMsec = 7500;
        NormalPixmap = new QPixmap(":/card/res/images/card/Peashooter.png");
        break;
    default:
        break;
    }
    
    PosX = (CardID <= 3) ? (43 + CardID * 57) : (45 + CardID * 57);
    PosY = 10;
    CurrentStatus = CardStatus::Normal;
    NormalCard = new QLabel(GlobalManager::CurrentWidget);
    NormalCard->setMouseTracking(true);
    DisableCard = new QLabel(GlobalManager::CurrentWidget);
    DisableCard->setMouseTracking(true);
    FreezeCard = new QLabel(GlobalManager::CurrentWidget);
    FreezeCard->setMouseTracking(true);
    NormalCard->setGeometry(ForScale(PosX), ForScale(PosY), ForScale(45), ForScale(63));
    DisableCard->setGeometry(ForScale(PosX), ForScale(PosY), ForScale(45), ForScale(63));
    FreezeCard->setGeometry(ForScale(PosX), ForScale(PosY), ForScale(45), ForScale(63));    
    GrayPixmap = new QPixmap(":/card/res/images/card/DisableCard.png");
    *GrayPixmap = GrayPixmap->scaled(ForScale(45), ForScale(63));
    *NormalPixmap = NormalPixmap->scaled(ForScale(45), ForScale(63));
    GrayEffect = new QGraphicsOpacityEffect;
    GrayEffect->setOpacity(0.5);
    FreezeCard->setPixmap(*GrayPixmap);
    FreezeCard->setGraphicsEffect(GrayEffect);
    DisableCard->setPixmap(*GrayPixmap);
    DisableCard->setGraphicsEffect(GrayEffect);
    NormalCard->setPixmap(*NormalPixmap);
    DisableCard->hide();
    FreezeCard->hide();
    NormalCard->show();
    FreezeTimer = new QTimer;
    FreezeTimer->setInterval(5);
    TimeUsed = 0;
    connect(FreezeTimer, SIGNAL(timeout()), this, SLOT(RecoveryFreeze()));
    CheckThis();
}

PlantCard::~PlantCard()
{
    delete GrayPixmap;
    delete NormalPixmap;
    delete NormalCard;
    delete DisableCard;
    delete FreezeCard;
    delete FreezeTimer;
}

void PlantCard::RecoveryFreeze()
{
    TimeUsed += 5;
    FreezeCard->resize(ForScale(45), ForScale(63 - 63 * TimeUsed * 1.0 / FreezeMsec));
    if(TimeUsed == FreezeMsec)
    {
        FreezeTimer->stop();
        TimeUsed = 0;
        CurrentStatus = CardStatus::Disable;
        FreezeCard->hide();
        CheckThis();
    }
}

void PlantCard::DisableThis(bool temp)
{
    if(temp)
    {
        DisableCard->show();
        CurrentStatus = CardStatus::Disable;        
    }
    else
    {
        DisableCard->hide();
        CurrentStatus = CardStatus::Normal;
    }
}

void PlantCard::FreezeThis()
{
    DisableCard->show();
    FreezeCard->show();
    CurrentStatus = CardStatus::Freezed;
    FreezeTimer->start();
}

void PlantCard::CheckThis()
{
    if(CurrentStatus == CardStatus::Freezed)
        return; 
    DisableThis(GlobalManager::SunNumber < SunCost);
}
