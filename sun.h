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
    explicit Sun(int FlowerRow, int FlowerColumn, QObject *parent = 0, int TempType = 25);
    ~Sun();
    
    int getType() const { return SunType; }
    Label *SunLabel;
    
private:
    int SunType;
    Mode SunMode;
    QMovie *SunGif;
    
    QTimer *FallTimer;
    QTimer *DelayTimer;
    QTimer *BackTimer;
    QTimer *FlowerTimer;

    int PosX, PosY;
    SunStatus CurrentStatus;
    int TimeUsed;
    
signals:
    void die(Sun*);
    void GetSunUp(int);
    
private slots:
    void SkyFall();
    void FlowerFall();
    void DelayDie();
    void GetSun();
    void SunBack();
    
public slots:
    void RaiseSun();
    void DeleteThis();
};

#endif // SUN_H
