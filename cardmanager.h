#ifndef CARDMANAGER_H
#define CARDMANAGER_H

#include <QObject>
#include <vector>
#include "plantcard.h"

class CardManager : public QObject
{
    Q_OBJECT
public:
    explicit CardManager(QObject *parent = 0);
    ~CardManager();
    
    std::vector<PlantCard*> CardVec;    
    
signals:
    void Pause();
    void Restart();
    void CheckAllCard();
    
public slots:

};

#endif // CARDMANAGER_H
