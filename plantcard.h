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
    
    PlantType getType() const;
    CardStatus getCardStatus();
    void DisableThis(bool);
    void FreezeThis();
    
signals:
    
public slots:
    void Pause();
    void Restart();
    void CheckThis();    
    
private slots:
    void ReFreeze();
    
private:
    PlantType m_Type;
    QPixmap *grayPic;
    QPixmap *NormalPic;
    QGraphicsOpacityEffect *m_GOE;
    QLabel *NormalCard;
    QLabel *DisableCard;
    QLabel *FreezeCard;
    QTimer *FreezeTimer;
    CardStatus CurrentStatus;
    
    int posX, posY;
    int SunCost;
    int Freezemsec;
    int TimeUsed;
};

#endif // PLANTCARD_H
