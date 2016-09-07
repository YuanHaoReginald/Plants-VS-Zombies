#ifndef WARMANAGER_H
#define WARMANAGER_H

#include <QObject>
#include "abstractplant.h"
#include "enumlist.h"

class WarManager : public QObject
{
    Q_OBJECT
public:
    explicit WarManager(QObject *parent = 0);
    
    AbstractPlant* grass[5][9];
signals:
   void  CostSun(int);
    
public slots:
    void RaisePlant(int, int, PlantType);
};

#endif // WARMANAGER_H
