#ifndef WARMANAGER_H
#define WARMANAGER_H

#include <QObject>
#include "abstractplant.h"
#include "pea.h"
#include "enumlist.h"
#include <QVector>

class WarManager : public QObject
{
    Q_OBJECT
public:
    explicit WarManager(QObject *parent = 0);
    ~WarManager();
    
    AbstractPlant* grass[5][9];
    QVector<Pea*> PeaManager[5];
    
signals:
   void CostSun(int);
   
private slots:
   void GeneratePea(int, int);
    
public slots:
    void RaisePlant(int, int, PlantType);
    void DeletePlant(AbstractPlant*);
    void DeletePea(Pea*);
};

#endif // WARMANAGER_H
