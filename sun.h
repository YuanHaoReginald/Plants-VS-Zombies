#ifndef SUN_H
#define SUN_H

#include <QObject>
#include <QMovie>
#include <QTimer>
#include "label.h"

class Sun : public QObject
{
    Q_OBJECT
    
public:
    enum class Mode { Fall, Flower };
    enum class SunStatus { Fall, Delay, Back };
    
public:
    explicit Sun(int FallSiteX, QObject *parent = 0, int TempType = 25);
    explicit Sun(int FlowerRow, int FlowerCulumn, QObject *parent = 0, int TempType = 25);
    ~Sun();
    
    int getType();
    Label *SunLabel;
    
private:
    int m_Type;
    Mode m_Mode;
    QMovie *SunGif;
    
    QTimer *FallTimer;
    QTimer *DelayTimer;
    QTimer *BackTimer;
    QTimer *FlowerTimer;

    int posX, posY;
    SunStatus CurrentStatus;
    int LeftMSec;
    int TimeUsed;
    
    
signals:
    void die(Sun*);
    void GetSunUp(int);
    
private slots:
    void FallEvent();
    void FlowerFall();
    void DelayDie();
    void GetSun();
    void SunBack();
    
public slots:
    void Pause();
    void Restart();
    void RaiseSun();
    void DeleteThis();
};

#endif // SUN_H
