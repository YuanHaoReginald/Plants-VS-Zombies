#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "abstractplant.h"
#include <QTimer>

class SunFlower : public AbstractPlant
{
    Q_OBJECT
public:
    SunFlower(int RowVal, int ColumnVal);
    ~SunFlower();
    
signals:
    void ProduceSun(int, int);
    
private slots:
    void ProduceSunSlot();
    
private:
    QTimer *ProduceSunTimer;
};

#endif // SUNFLOWER_H
