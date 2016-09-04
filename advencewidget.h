#ifndef ADVENCEWIDGET_H
#define ADVENCEWIDGET_H

#include "abstractwidget.h"
#include "sunmanager.h"
#include <QLabel>
#include <QPixmap>
#include <QTimer>

class AdvenceWidget : public AbstractWidget
{
    Q_OBJECT
    
public:
    explicit AdvenceWidget(QWidget *parent);
    ~AdvenceWidget() { }
    
    QPixmap *getReadPixmap() const;
    void setReadPixmap(QPixmap *value);
    
private:
    enum class MainTimerStatus { Delay1, Push1Up, Push1Down, Delay2, Push2Up, Push2Down, 
                                 StartSet, StartReady, StartPlant, RealGame };
    
    QLabel *GrassBackgroundLabel;
    QPixmap *GrassBackgroundPixmap;
    
    QTimer *MainTimer;
    MainTimerStatus CurrentMainTimerStatus;
    
    QLabel *MenuLabel;
    QLabel *CardSlotLabel;
    QLabel *ShovelBackLabel;
    QLabel *ShovelLabel;
    QLabel *ReadyLabel;
    QPixmap *MenuPixmap;
    QPixmap *CardSlotPixmap;
    QPixmap *ShovelBackPixmap;
    QPixmap *ShovelPixmap;
    QPixmap *ReadyPixmap;
    SunManager *GlobalSunManager;
    
    
private slots:
    void SlotOfMainTimer();
};

#endif // ADVENCEWIDGET_H
