#ifndef ABSTRACTPLANT_H
#define ABSTRACTPLANT_H

#include <QObject>
#include <QLabel>
#include <QMovie>
#include "enumlist.h"

class AbstractPlant : public QObject
{
    Q_OBJECT
public:
    explicit AbstractPlant(QObject *parent = 0) : QObject(parent) { }
    ~AbstractPlant();
    
    PlantType getType() const { return ThisPlantType; }
    int getRow() const { return Row; }
    int getCulumn() const { return Column; }
    int getWidth() const { return Width; }
    int getHeight() const { return Height; }
    virtual void getAttack();
    
signals:
    die(AbstractPlant*);
    
protected:
    PlantType ThisPlantType;
    int Blood;
    int Row, Column;
    QLabel* PlantLabel;
    QMovie* PlantMovie;
    int Width, Height;
};

#endif // ABSTRACTPLANT_H
