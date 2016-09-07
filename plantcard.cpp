#include "plantcard.h"
#include "globalmanager.h"
#include <QPixmap>

PlantCard::PlantCard(PlantType TypeVal, int CardID, QObject *parent) : QObject(parent), m_Type(TypeVal)
{
    switch(TypeVal)
    {
    case PlantType::SunFlower:
        SunCost = 50;
        Freezemsec = 7500;
        NormalPic = new QPixmap(":/card/res/images/card/Sunflower.png");
        break;
    case PlantType::WallNut:
        SunCost = 50;
        Freezemsec = 30000;
        NormalPic = new QPixmap(":/card/res/images/card/WallNut.png");
        break;
    case PlantType::Peashooter:
        SunCost = 100;
        Freezemsec = 7500;
        NormalPic = new QPixmap(":/card/res/images/card/Peashooter.png");
        break;
    case PlantType::Chomper:
        SunCost = 150;
        Freezemsec = 7500;
        NormalPic = new QPixmap(":/card/res/images/card/Chomper.png");
        break;
    default:
        break;
    }
    
    posX = (CardID <= 3) ? (43 + CardID * 57) : (45 + CardID * 57);
    posY = 10;
    CurrentStatus = CardStatus::Normal;
    NormalCard = new QLabel(GlobalManager::CurrentWidget);
    NormalCard->setMouseTracking(true);
    DisableCard = new QLabel(GlobalManager::CurrentWidget);
    DisableCard->setMouseTracking(true);
    FreezeCard = new QLabel(GlobalManager::CurrentWidget);
    FreezeCard->setMouseTracking(true);
    NormalCard->setGeometry(ForScale(posX), ForScale(posY), ForScale(45), ForScale(63));
    DisableCard->setGeometry(ForScale(posX), ForScale(posY), ForScale(45), ForScale(63));
    FreezeCard->setGeometry(ForScale(posX), ForScale(posY), ForScale(45), ForScale(63));    
    grayPic = new QPixmap(":/card/res/images/card/DisableCard.png");
    *grayPic = grayPic->scaled(ForScale(45), ForScale(63));
    *NormalPic = NormalPic->scaled(ForScale(45), ForScale(63));
    m_GOE = new QGraphicsOpacityEffect;
    m_GOE->setOpacity(0.5);
    FreezeCard->setPixmap(*grayPic);
    FreezeCard->setGraphicsEffect(m_GOE);
    DisableCard->setPixmap(*grayPic);
    DisableCard->setGraphicsEffect(m_GOE);
    NormalCard->setPixmap(*NormalPic);
    DisableCard->hide();
    FreezeCard->hide();
    NormalCard->show();
    FreezeTimer = new QTimer;
    FreezeTimer->setInterval(5);
    TimeUsed = 0;
    connect(FreezeTimer, SIGNAL(timeout()), this, SLOT(ReFreeze()));
    CheckThis();
}

PlantCard::~PlantCard()
{
    delete grayPic;
    delete NormalPic;
    delete NormalCard;
    delete DisableCard;
    delete FreezeCard;
    delete FreezeTimer;
}

PlantType PlantCard::getType() const
{
    return m_Type;
}

CardStatus PlantCard::getCardStatus()
{
    return CurrentStatus;
}

void PlantCard::Pause()
{
    if(CurrentStatus == CardStatus::Freezed)
    {
        FreezeTimer->stop();
    }
}

void PlantCard::Restart()
{
    if(CurrentStatus == CardStatus::Freezed)
    {
        FreezeTimer->start();
    }
}

void PlantCard::ReFreeze()
{
    TimeUsed += 5;
    FreezeCard->setGeometry(ForScale(posX), ForScale(posY), ForScale(45), 
                            ForScale(63 - 63 * TimeUsed * 1.0 / Freezemsec));
    if(TimeUsed == Freezemsec)
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
    
    DisableThis(GlobalManager::NumberOfSun < SunCost);
}
