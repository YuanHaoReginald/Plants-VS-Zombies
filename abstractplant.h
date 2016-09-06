#ifndef ABSTRACTPLANT_H
#define ABSTRACTPLANT_H

#include <QObject>
#include <QLabel>
#include <QMovie>
#include "globalmanager.h"

class AbstractPlant : public QObject
{
    Q_OBJECT
public:
    explicit AbstractPlant(QObject *parent = 0);
    ~AbstractPlant();
    
    PlantType getType();
    int getRow();
    int getCulumn();
    int getWidth();
    int getHeight();
    virtual void getAttack();
    
signals:
    die();
    
public slots:
    virtual void Pause() = 0;
    virtual void Restart() = 0;
    
protected:
    PlantType m_Type;
    int blood;
    int Row, Culumn;
    QLabel* PlantLabel;
    QMovie* PlantMovie;
    int width, height;
};

#endif // ABSTRACTPLANT_H
