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
    ~WarManager();
    
    AbstractPlant* grass[5][9];
signals:
   void CostSun(int);
   
private slots:
   void GeneratePea(int, int);
    
public slots:
    void RaisePlant(int, int, PlantType);
    void DeletePlant(AbstractPlant*);
};

#endif // WARMANAGER_H
