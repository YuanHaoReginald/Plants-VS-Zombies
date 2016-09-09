#ifndef ADVENCEWIDGET_H
#define ADVENCEWIDGET_H

#include "abstractwidget.h"
#include "sunmanager.h"
#include "warmanager.h"
#include "cardmanager.h"
#include "enumlist.h"
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QMouseEvent>
#include <QGraphicsOpacityEffect>
#include <QMediaPlayer>

class AdvenceWidget : public AbstractWidget
{
    Q_OBJECT
    
public:
    explicit AdvenceWidget(QWidget *parent);
    ~AdvenceWidget();
    
    QPixmap *getReadPixmap() const;
    void setReadPixmap(QPixmap *value);
    
signals:
    void HasPlanted(PlantType);
    
private:
    enum class MainTimerStatus { Delay1, Push1Up, Push1Down, Delay2, Push2Up, Push2Down, 
                                 StartSet, StartReady, StartPlant, RealGame, HasStarted };
    enum class ScreenArea { Card, Grass, Shovel, Pause };
    
    QLabel *GrassBackgroundLabel;
    QPixmap *GrassBackgroundPixmap;
    
    QTimer *MainTimer;
    MainTimerStatus CurrentMainTimerStatus;
    
    QLabel *MenuLabel;
    QLabel *CardSlotLabel;
    QLabel *ShovelBackLabel;
    QLabel *ShovelLabel;
    QLabel *ReadyLabel;
    QLabel *MouseLabel;
    QLabel *VirtualPlant;
    QPixmap *MenuPixmap;
    QPixmap *CardSlotPixmap;
    QPixmap *ShovelBackPixmap;
    QPixmap *ShovelPixmap;
    QPixmap *ReadyPixmap;
    QPixmap *MousePixmap;
    QPixmap *VirtualPlantPixmap;
    QMediaPlayer* AdvenceMediaPlayer;

    QGraphicsOpacityEffect *m_GOE;
    
    PlantType MouseType;
    
    //bool InGrassArea(int, int, int, int);
    bool InCardArea(int, int, int);
    
private slots:
    void SlotOfMainTimer();
    void SwitchMouseType(PlantType, int, int);
    
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // ADVENCEWIDGET_H
