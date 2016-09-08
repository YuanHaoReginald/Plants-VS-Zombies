#ifndef WARMANAGER_H
#define WARMANAGER_H

#include <QObject>
#include "abstractplant.h"
#include "abstractzombie.h"
#include "pea.h"
#include "enumlist.h"
#include <QVector>
#include <QTimer>

class WarManager : public QObject
{
    Q_OBJECT
public:
    explicit WarManager(QObject *parent = 0);
    ~WarManager();
    
    AbstractPlant* grass[5][9];
    QVector<Pea*> PeaManager[5];
    AbstractZombie* ZombieManager[150];
    
signals:
    void CostSun(int);
   
private slots:
    void GeneratePea(int, int);
    void GenerateZombie();
    void ClockUpdate();
    
public slots:
    void RaisePlant(int, int, PlantType);
    void DeletePlant(AbstractPlant*);
    void DeletePea(Pea*);
    
private:
    QTimer *WarClock;
    int firstZombie, lastZombie;
    int GenerateZombieClockNow, GenerateZombieClockLimit;
};

#endif // WARMANAGER_H
