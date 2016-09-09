#include "advencewidget.h"
#include "globalmanager.h"
#include "enumlist.h"
#include "managermanager.h"
#include <QGraphicsOpacityEffect>
#include <QDebug>

AdvenceWidget::AdvenceWidget(QWidget *parent) : AbstractWidget(parent)
{
    setFixedWidth(ForScale(GlobalManager::StanradWindowWidth));
    setFixedHeight(ForScale(GlobalManager::StanradWindowWHeight));
    setMouseTracking(true);
    MouseLabel = new QLabel(this);
    MouseLabel->setMouseTracking(true);
    MousePixmap = new QPixmap;
    MouseLabel->setPixmap(*MousePixmap);
    MouseLabel->hide();
    MouseType = PlantType::NoPlant;
    m_GOE = new QGraphicsOpacityEffect;
    m_GOE->setOpacity(0.5);
    VirtualPlant = new QLabel(this);
    VirtualPlant->setMouseTracking(true);
    VirtualPlantPixmap = new QPixmap;
    VirtualPlant->setPixmap(*VirtualPlantPixmap);
    VirtualPlant->hide();
    ReadyLabel = nullptr;
    ReadyPixmap = nullptr;
    
    GrassBackgroundPixmap = new QPixmap(":/surface/res/images/surface/NormalGrass.png");
    *GrassBackgroundPixmap = GrassBackgroundPixmap->scaled(ForScale(1400), ForScale(600), Qt::KeepAspectRatio);
    GrassBackgroundLabel = new QLabel(this);
    GrassBackgroundLabel->setMouseTracking(true);
    GrassBackgroundLabel->setGeometry(0, 0, ForScale(1400), ForScale(600));
    GrassBackgroundLabel->setPixmap(*GrassBackgroundPixmap);
    CurrentMainTimerStatus = MainTimerStatus::Delay1;
    MainTimer = new QTimer;
    connect(MainTimer, SIGNAL(timeout()), this, SLOT(SlotOfMainTimer()));
    QTimer::singleShot(1500, this, SLOT(SlotOfMainTimer()));
    //QTimer::singleShot(15, this, SLOT(SlotOfMainTimer()));    
    
    MenuPixmap = new QPixmap(":/surface/res/images/surface/MenuButtonNormal.png");
    *MenuPixmap = MenuPixmap->scaled(ForScale(113), ForScale(35), Qt::KeepAspectRatio);
    MenuLabel = new QLabel(this);
    MenuLabel->setMouseTracking(true);
    MenuLabel->setGeometry(ForScale(780), ForScale(-6), ForScale(113), ForScale(35));
    MenuLabel->setPixmap(*MenuPixmap);
    MenuLabel->hide();

    CardSlotPixmap = new QPixmap(":/surface/res/images/surface/CardSlot.png");
    *CardSlotPixmap = CardSlotPixmap->scaled(ForScale(435), ForScale(84), Qt::KeepAspectRatio);
    CardSlotLabel = new QLabel(this);
    CardSlotLabel->setMouseTracking(true);
    CardSlotLabel->setGeometry(ForScale(15), 0, ForScale(435), ForScale(84));
    CardSlotLabel->setPixmap(*CardSlotPixmap);
    CardSlotLabel->hide();
    
    ShovelBackPixmap = new QPixmap(":/surface/res/images/surface/ShovelBack.png");
    *ShovelBackPixmap = ShovelBackPixmap->scaled(ForScale(71), ForScale(72), Qt::KeepAspectRatio);
    ShovelBackLabel = new QLabel(this);
    ShovelBackLabel->setMouseTracking(true);
    ShovelBackLabel->setGeometry(ForScale(450), 0, ForScale(71), ForScale(72));
    ShovelBackLabel->setPixmap(*ShovelBackPixmap);
    ShovelBackLabel->hide();
    
    ShovelPixmap = new QPixmap(":/surface/res/images/surface/Shovel.png");
    *ShovelPixmap = ShovelPixmap->scaled(ForScale(53), ForScale(57), Qt::KeepAspectRatio);
    ShovelLabel = new QLabel(this);
    ShovelLabel->setMouseTracking(true);
    ShovelLabel->setGeometry(ForScale(459), ForScale(8), ForScale(53), ForScale(57));
    ShovelLabel->setPixmap(*ShovelPixmap);
    ShovelLabel->hide();
    
    AdvenceMediaPlayer = new QMediaPlayer;
    AdvenceMediaPlayer->setMedia(QUrl("qrc:/background/res/audio/Kitanai Sekai.mp3"));
    AdvenceMediaPlayer->setVolume(30);
    AdvenceMediaPlayer->play();
}

AdvenceWidget::~AdvenceWidget()
{
    delete GrassBackgroundLabel;
    delete GrassBackgroundPixmap;
    delete MainTimer;
    delete MenuLabel;
    delete CardSlotLabel;
    delete ShovelBackLabel;
    delete ShovelLabel;
    delete ReadyLabel;
    delete MouseLabel;
    delete MenuPixmap;
    delete CardSlotPixmap;
    delete ShovelBackPixmap;
    delete ShovelPixmap;
    delete ReadyPixmap;
    delete MousePixmap;
    delete ManagerManager::GlobalSunManager;
    ManagerManager::GlobalSunManager = nullptr;
    delete ManagerManager::GlobalCardManager;
    ManagerManager::GlobalCardManager = nullptr;
    delete ManagerManager::GlobalWarManager;
    ManagerManager::GlobalWarManager = nullptr;
    delete m_GOE;
    delete VirtualPlant;
    delete VirtualPlantPixmap;
    delete AdvenceMediaPlayer;
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
            QTimer::singleShot(1000, this, SLOT(SlotOfMainTimer()));
            //QTimer::singleShot(10, this, SLOT(SlotOfMainTimer()));            
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
        ReadyLabel->setMouseTracking(true);
        ReadyLabel->setGeometry(ForScale(300), ForScale(233), ForScale(300), ForScale(133));
        ReadyLabel->setPixmap(*ReadyPixmap);
        ReadyLabel->show();
        QTimer::singleShot(1000, this, SLOT(SlotOfMainTimer()));   
        //QTimer::singleShot(10, this, SLOT(SlotOfMainTimer()));           
        CurrentMainTimerStatus = MainTimerStatus::StartReady;
        break;
    case MainTimerStatus::StartReady:
        ReadyPixmap->load(":/surface/res/images/surface/StartReady.png");
        *ReadyPixmap = ReadyPixmap->scaled(ForScale(300), ForScale(133), Qt::KeepAspectRatio);
        ReadyLabel->setPixmap(*ReadyPixmap);
        QTimer::singleShot(1000, this, SLOT(SlotOfMainTimer()));   
        //QTimer::singleShot(10, this, SLOT(SlotOfMainTimer()));           
        CurrentMainTimerStatus = MainTimerStatus::StartPlant;
        break;
    case MainTimerStatus::StartPlant:
        ReadyPixmap->load(":/surface/res/images/surface/StartPlant.png");
        *ReadyPixmap = ReadyPixmap->scaled(ForScale(300), ForScale(133), Qt::KeepAspectRatio);
        ReadyLabel->setPixmap(*ReadyPixmap);
        QTimer::singleShot(1000, this, SLOT(SlotOfMainTimer()));   
        //QTimer::singleShot(10, this, SLOT(SlotOfMainTimer()));           
        CurrentMainTimerStatus = MainTimerStatus::RealGame;
        break;
    case MainTimerStatus::RealGame:
        delete ReadyLabel;
        delete ReadyPixmap;
        ReadyLabel = nullptr;
        ReadyPixmap = nullptr;
        ManagerManager::GlobalSunManager = new SunManager(this);
        ManagerManager::GlobalSunManager->Start();
        MenuLabel->show();
        CardSlotLabel->show();
        ShovelBackLabel->show();
        ShovelLabel->show();
        ManagerManager::GlobalCardManager = new CardManager(this);
        ManagerManager::GlobalWarManager = new WarManager(this);
        connect(ManagerManager::GlobalSunManager, SIGNAL(SunNumberUpdate()),
                ManagerManager::GlobalCardManager, SIGNAL(CheckAllCard()));
        connect(ManagerManager::GlobalWarManager, SIGNAL(CostSun(int)),
                ManagerManager::GlobalSunManager, SLOT(MinusSunNumber(int)));
        connect(this, SIGNAL(HasPlanted(PlantType)),
                ManagerManager::GlobalCardManager, SLOT(FreezeSomeone(PlantType)));
        connect(ManagerManager::GlobalWarManager, SIGNAL(EndGame(GameStatus)),
                this, SIGNAL(StatusChanged(GameStatus)));
        CurrentMainTimerStatus = MainTimerStatus::HasStarted;        
        break;
    default:
        break;
    }
}

void AdvenceWidget::SwitchMouseType(PlantType PLVal, int xVal, int yVal)
{
    if(PLVal == MouseType)
        return;
    MouseType = PLVal;
    delete MousePixmap;
    
    switch (MouseType) {
    case PlantType::SunFlower:
        MousePixmap = new QPixmap(":/plant/res/images/plant/SunFlower/0.gif");
        *MousePixmap = MousePixmap->scaled(ForScale(63), ForScale(72));
        MouseLabel->setPixmap(*MousePixmap);
        MouseLabel->setGeometry(xVal - ForScale(63 / 2), yVal - ForScale(72 / 2),
                                ForScale(63), ForScale(72));
        MouseLabel->show();
        MouseLabel->raise();
        break;
    case PlantType::Peashooter:
        MousePixmap = new QPixmap(":/plant/res/images/plant/Peashooter/0.gif");
        *MousePixmap = MousePixmap->scaled(ForScale(62), ForScale(70));
        MouseLabel->setPixmap(*MousePixmap);
        MouseLabel->setGeometry(xVal - ForScale(62 / 2), yVal - ForScale(70 / 2),
                                ForScale(62), ForScale(70));
        MouseLabel->show();
        MouseLabel->raise();
        break;
    case PlantType::WallNut:
        MousePixmap = new QPixmap(":/plant/res/images/plant/WallNut/0.gif");
        *MousePixmap = MousePixmap->scaled(ForScale(61), ForScale(71));
        MouseLabel->setPixmap(*MousePixmap);
        MouseLabel->setGeometry(xVal - ForScale(61 / 2), yVal - ForScale(71 / 2),
                                ForScale(61), ForScale(71));
        MouseLabel->show();
        MouseLabel->raise();
        break;
    case PlantType::Shovel:
        MousePixmap = new QPixmap;
        MouseLabel->hide();
        ShovelLabel->move(xVal - ForScale(53 / 2), yVal - ForScale(57 / 2));
        ShovelLabel->raise();
        break;        
    case PlantType::NoPlant:
        MousePixmap = new QPixmap;
        MouseLabel->hide();
        break;
    default:
        break;
    }
}

void AdvenceWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(CurrentMainTimerStatus == MainTimerStatus::HasStarted)
    {
        switch(MouseType)
        {
        case PlantType::SunFlower:
            MouseLabel->move(event->x() - ForScale(63 / 2), event->y() - ForScale(72 / 2));
            MouseLabel->show();
            MouseLabel->raise();
            break;
        case PlantType::Peashooter:
            MouseLabel->move(event->x() - ForScale(62 / 2), event->y() - ForScale(70 / 2));
            MouseLabel->show();
            MouseLabel->raise();
            break;
        case PlantType::WallNut:
            MouseLabel->move(event->x() - ForScale(61 / 2), event->y() - ForScale(71 / 2));
            MouseLabel->show();
            MouseLabel->raise();
            break;
        case PlantType::Shovel:
            ShovelLabel->move(event->x() - ForScale(53 / 2), event->y() - ForScale(57 / 2));
            ShovelLabel->show();
            ShovelLabel->raise();
            break;
        default:
            break;
        }
        
        if(MouseType != PlantType::NoPlant && MouseType != PlantType::Shovel)
        {
            if(event->x() >= ForScale(GlobalManager::posX[0]) 
                    && event->x() < ForScale(GlobalManager::posX[9])
                    && event->y() >= ForScale(GlobalManager::posY[0]) 
                    && event->y() < ForScale(GlobalManager::posY[5]))
            {
                int CulumnTemp = (event->x() - ForScale(GlobalManager::posX[0])) / ForScale(80) + 1;
                int RowTemp = (event->y() - ForScale(GlobalManager::posY[0])) / ForScale(94) + 1;
                if(ManagerManager::GlobalWarManager->grass[RowTemp - 1][CulumnTemp - 1] == nullptr)
                {
                    switch(MouseType)
                    {
                    case PlantType::SunFlower:
                        VirtualPlantPixmap->load(":/plant/res/images/plant/SunFlower/0.gif");
                        *VirtualPlantPixmap = VirtualPlantPixmap->scaled(ForScale(63), ForScale(72));
                        VirtualPlant->setPixmap(*VirtualPlantPixmap);
                        VirtualPlant->setGraphicsEffect(m_GOE);
                        VirtualPlant->setGeometry(ForScale(GlobalManager::posX[CulumnTemp] - 40 - 63 / 2), 
                                                  ForScale(GlobalManager::posY[RowTemp] - 47 - 72 / 2),
                                                  ForScale(63), ForScale(72));
                        break;
                    case PlantType::Peashooter:
                        VirtualPlantPixmap->load(":/plant/res/images/plant/Peashooter/0.gif");
                        *VirtualPlantPixmap = VirtualPlantPixmap->scaled(ForScale(62), ForScale(70));
                        VirtualPlant->setPixmap(*VirtualPlantPixmap);                        
                        VirtualPlant->setGraphicsEffect(m_GOE);
                        VirtualPlant->setGeometry(ForScale(GlobalManager::posX[CulumnTemp] - 40 - 62 / 2), 
                                                  ForScale(GlobalManager::posY[RowTemp] - 47 - 70 / 2),
                                                  ForScale(62), ForScale(70));

                        break;
                    case PlantType::WallNut:
                        VirtualPlantPixmap->load(":/plant/res/images/plant/WallNut/0.gif");
                        *VirtualPlantPixmap = VirtualPlantPixmap->scaled(ForScale(61), ForScale(71));
                        VirtualPlant->setPixmap(*VirtualPlantPixmap);                        
                        VirtualPlant->setGraphicsEffect(m_GOE);
                        VirtualPlant->setGeometry(ForScale(GlobalManager::posX[CulumnTemp] - 40 - 61 / 2), 
                                                  ForScale(GlobalManager::posY[RowTemp] - 47 - 71 / 2),
                                                  ForScale(61), ForScale(71));
                        break;
                    default:
                        break;
                    }
                    VirtualPlant->show();
                    VirtualPlant->raise();
                    MouseLabel->raise();
                }
                else
                    VirtualPlant->hide();
                
            }
            else 
                VirtualPlant->hide();
            
        }
        else
            VirtualPlant->hide();
    }
    AbstractWidget::mouseMoveEvent(event);
}

void AdvenceWidget::mousePressEvent(QMouseEvent *event)
{
    if(CurrentMainTimerStatus == MainTimerStatus::HasStarted)
    {
        if(MouseType == PlantType::NoPlant)
        {
            if(InCardArea(1, event->x(), event->y()) 
                    && ManagerManager::GlobalCardManager->CardVec[0]->getCardStatus() == CardStatus::Normal)
                SwitchMouseType(ManagerManager::GlobalCardManager->CardVec[0]->getType(),
                        event->x(), event->y());
            else if(InCardArea(2, event->x(), event->y()) 
                    && ManagerManager::GlobalCardManager->CardVec[1]->getCardStatus() == CardStatus::Normal)
                SwitchMouseType(ManagerManager::GlobalCardManager->CardVec[1]->getType(),
                        event->x(), event->y());
            else if(InCardArea(3, event->x(), event->y()) 
                    && ManagerManager::GlobalCardManager->CardVec[2]->getCardStatus() == CardStatus::Normal)
                SwitchMouseType(ManagerManager::GlobalCardManager->CardVec[2]->getType(),
                        event->x(), event->y());
            else if(event->x() >= ForScale(459) && event->x() < ForScale(512)
                    && event->y() >= ForScale(8) && event->y() <= ForScale(65))
                SwitchMouseType(PlantType::Shovel, event->x(), event->y());
        }
        else
        {
            if(event->x() >= ForScale(GlobalManager::posX[0]) 
                    && event->x() <= ForScale(GlobalManager::posX[9])
                    && event->y() >= ForScale(GlobalManager::posY[0]) 
                    && event->y() <= ForScale(GlobalManager::posY[5]))
            {
                int CulumnTemp = (event->x() - ForScale(GlobalManager::posX[0])) / ForScale(80) + 1;
                int RowTemp = (event->y() - ForScale(GlobalManager::posY[0])) / ForScale(94) + 1;
                if(MouseType != PlantType::Shovel 
                        && ManagerManager::GlobalWarManager->grass[RowTemp - 1][CulumnTemp - 1] == nullptr)
                {
                    ManagerManager::GlobalWarManager->RaisePlant(RowTemp, CulumnTemp, MouseType);
                    emit HasPlanted(MouseType);
                }
                else if(MouseType == PlantType::Shovel
                        && ManagerManager::GlobalWarManager->grass[RowTemp - 1][CulumnTemp - 1] != nullptr)
                {
                    delete ManagerManager::GlobalWarManager->grass[RowTemp - 1][CulumnTemp - 1];
                    ManagerManager::GlobalWarManager->grass[RowTemp - 1][CulumnTemp - 1] = nullptr;
                }
            }
            VirtualPlant->hide();
            ShovelLabel->move(ForScale(459), ForScale(8));
            SwitchMouseType(PlantType::NoPlant, event->x(), event->y());
        }
    }
    AbstractWidget::mousePressEvent(event);
}

bool AdvenceWidget::InCardArea(int CardID, int x, int y)
{
    int posX = (CardID <= 3) ? (43 + CardID * 57) : (45 + CardID * 57);
    int posY = 10;
    if(x >= ForScale(posX) && x <= ForScale(posX + 45) && y >= ForScale(posY) && y <= ForScale(posY + 63))
        return true;
    else
        return false;
}
