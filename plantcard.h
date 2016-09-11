#ifndef PLANTCARD_H
#define PLANTCARD_H

#include <QObject>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include "globalmanager.h"

class PlantCard : public QObject
{
    Q_OBJECT
public:
    explicit PlantCard(PlantType TypeVal, int CardID, QObject *parent = 0);
    ~PlantCard();
    
    PlantType getType() const { return CardType; }
    CardStatus getCardStatus() const {return CurrentStatus; }
    void DisableThis(bool);
    void FreezeThis();
       
public slots:
    void CheckThis();    
    
private slots:
    void RecoveryFreeze();
    
private:
    PlantType CardType;
    QPixmap *GrayPixmap;
    QPixmap *NormalPixmap;
    QGraphicsOpacityEffect *GrayEffect;
    QLabel *NormalCard;
    QLabel *DisableCard;
    QLabel *FreezeCard;
    QTimer *FreezeTimer;
    CardStatus CurrentStatus;
    
    int PosX, PosY;
    int SunCost;
    int FreezeMsec;
    int TimeUsed;
};

#endif // PLANTCARD_H
