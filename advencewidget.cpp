#include "advencewidget.h"
#include "globalmanager.h"
#include <QtDebug>

AdvenceWidget::AdvenceWidget(QWidget *parent) : AbstractWidget(parent)
{
    setFixedWidth(ForScale(GlobalManager::StanradWindowWidth));
    setFixedHeight(ForScale(GlobalManager::StanradWindowWHeight));
    
    GrassBackgroundPixmap = new QPixmap(":/surface/res/images/surface/NormalGrass.png");
    *GrassBackgroundPixmap = GrassBackgroundPixmap->scaled(ForScale(1400), ForScale(600), Qt::KeepAspectRatio);
    GrassBackgroundLabel = new QLabel(this);
    GrassBackgroundLabel->setGeometry(0, 0, ForScale(1400), ForScale(600));
    GrassBackgroundLabel->setPixmap(*GrassBackgroundPixmap);
    CurrentMainTimerStatus = MainTimerStatus::Delay1;
    MainTimer = new QTimer;
    connect(MainTimer, SIGNAL(timeout()), this, SLOT(SlotOfMainTimer()));
    QTimer::singleShot(1500, this, SLOT(SlotOfMainTimer()));
    
    MenuPixmap = new QPixmap(":/surface/res/images/surface/MenuButtonNormal.png");
    *MenuPixmap = MenuPixmap->scaled(ForScale(113), ForScale(35), Qt::KeepAspectRatio);
    MenuLabel = new QLabel(this);
    MenuLabel->setGeometry(ForScale(780), ForScale(-6), ForScale(113), ForScale(35));
    MenuLabel->setPixmap(*MenuPixmap);
    MenuLabel->hide();

    CardSlotPixmap = new QPixmap(":/surface/res/images/surface/CardSlot.png");
    *CardSlotPixmap = CardSlotPixmap->scaled(ForScale(435), ForScale(84), Qt::KeepAspectRatio);
    CardSlotLabel = new QLabel(this);
    CardSlotLabel->setGeometry(ForScale(15), 0, ForScale(435), ForScale(84));
    CardSlotLabel->setPixmap(*CardSlotPixmap);
    CardSlotLabel->hide();
    
    ShovelBackPixmap = new QPixmap(":/surface/res/images/surface/ShovelBack.png");
    *ShovelBackPixmap = ShovelBackPixmap->scaled(ForScale(71), ForScale(72), Qt::KeepAspectRatio);
    ShovelBackLabel = new QLabel(this);
    ShovelBackLabel->setGeometry(ForScale(450), 0, ForScale(71), ForScale(72));
    ShovelBackLabel->setPixmap(*ShovelBackPixmap);
    ShovelBackLabel->hide();
    
    ShovelPixmap = new QPixmap(":/surface/res/images/surface/Shovel.png");
    *ShovelPixmap = ShovelPixmap->scaled(ForScale(53), ForScale(57), Qt::KeepAspectRatio);
    ShovelLabel = new QLabel(this);
    ShovelLabel->setGeometry(ForScale(459), 8, ForScale(53), ForScale(57));
    ShovelLabel->setPixmap(*ShovelPixmap);
    ShovelLabel->hide();
}

QPixmap *AdvenceWidget::getReadPixmap() const
{
    return ReadyPixmap;
}

void AdvenceWidget::setReadPixmap(QPixmap *value)
{
    ReadyPixmap = value;
}

void AdvenceWidget::SlotOfMainTimer()
{
    static int PushTimeUsed = 0;
    switch(CurrentMainTimerStatus)
    {
    case MainTimerStatus::Delay1:
        CurrentMainTimerStatus = MainTimerStatus::Push1Up;
        MainTimer->setInterval(5);
        MainTimer->start();
        break;
    case MainTimerStatus::Push1Up:
        PushTimeUsed += 5;
        GrassBackgroundLabel->setGeometry(ForScale(-0.001 * PushTimeUsed * PushTimeUsed), 0,
                                          ForScale(1400), ForScale(600));
        if(PushTimeUsed == 500)
            CurrentMainTimerStatus = MainTimerStatus::Push1Down;
        break;
    case MainTimerStatus::Push1Down:
        PushTimeUsed += 5;
        GrassBackgroundLabel->setGeometry(ForScale(0.001 * PushTimeUsed * PushTimeUsed 
                                                   - 2 * PushTimeUsed + 500),
                                          0, ForScale(1400), ForScale(600));
        if(PushTimeUsed == 1000)
        {
            MainTimer->stop();
            CurrentMainTimerStatus = MainTimerStatus::Delay2;
            QTimer::singleShot(1500, this, SLOT(SlotOfMainTimer()));
        }
        break;
    case MainTimerStatus::Delay2:
        PushTimeUsed = 0;
        CurrentMainTimerStatus = MainTimerStatus::Push2Up;
        MainTimer->start();
        break;
    case MainTimerStatus::Push2Up:
        PushTimeUsed += 5;
        GrassBackgroundLabel->setGeometry(ForScale(PushTimeUsed * PushTimeUsed * 1.0 / 760 - 500), 0,
                                          ForScale(1400), ForScale(600));
        if(PushTimeUsed == 380)
            CurrentMainTimerStatus = MainTimerStatus::Push2Down;
        break;
    case MainTimerStatus::Push2Down:
        PushTimeUsed += 5;
        GrassBackgroundLabel->setGeometry(ForScale(PushTimeUsed * PushTimeUsed * (-1.0) / 760 
                                                   + 2 * PushTimeUsed - 880),
                                          0, ForScale(1400), ForScale(600));
        if(PushTimeUsed == 760)
        {
            CurrentMainTimerStatus = MainTimerStatus::StartSet;
            MainTimer->stop();
            QTimer::singleShot(100, this, SLOT(SlotOfMainTimer()));
        }
        break;
    case MainTimerStatus::StartSet:
        ReadyPixmap = new QPixmap(":/surface/res/images/surface/StartSet.png");
        *ReadyPixmap = ReadyPixmap->scaled(ForScale(300), ForScale(133), Qt::KeepAspectRatio);
        ReadyLabel = new QLabel(this);
        ReadyLabel->setGeometry(ForScale(300), ForScale(233), ForScale(300), ForScale(133));
        ReadyLabel->setPixmap(*ReadyPixmap);
        ReadyLabel->show();
        QTimer::singleShot(1000, this, SLOT(SlotOfMainTimer()));   
        CurrentMainTimerStatus = MainTimerStatus::StartReady;
        break;
    case MainTimerStatus::StartReady:
        ReadyPixmap->load(":/surface/res/images/surface/StartReady.png");
        *ReadyPixmap = ReadyPixmap->scaled(ForScale(300), ForScale(133), Qt::KeepAspectRatio);
        ReadyLabel->setPixmap(*ReadyPixmap);
        QTimer::singleShot(1000, this, SLOT(SlotOfMainTimer()));   
        CurrentMainTimerStatus = MainTimerStatus::StartPlant;
        break;
    case MainTimerStatus::StartPlant:
        ReadyPixmap->load(":/surface/res/images/surface/StartPlant.png");
        *ReadyPixmap = ReadyPixmap->scaled(ForScale(300), ForScale(133), Qt::KeepAspectRatio);
        ReadyLabel->setPixmap(*ReadyPixmap);
        QTimer::singleShot(1000, this, SLOT(SlotOfMainTimer()));   
        CurrentMainTimerStatus = MainTimerStatus::ReadGame;
        break;
    case MainTimerStatus::ReadGame:
        delete ReadyLabel;
        delete ReadyPixmap;
        ReadyLabel = nullptr;
        ReadyPixmap = nullptr;
        MenuLabel->show();
        CardSlotLabel->show();
        ShovelBackLabel->show();
        ShovelLabel->show();
        break;
    default:
        break;
    }
}
