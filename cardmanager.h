#ifndef CARDMANAGER_H
#define CARDMANAGER_H

#include <QObject>
#include <vector>
#include "plantcard.h"
#include "enumlist.h"

class CardManager : public QObject
{
    Q_OBJECT
public:
    explicit CardManager(QObject *parent = 0);
    ~CardManager();
    
    std::vector<PlantCard*> CardVec;    
    
signals:
    void CheckAllCard();
    
public slots:
    void FreezeSomeone(PlantType);
};

#endif // CARDMANAGER_H
