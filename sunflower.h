#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "abstractplant.h"
#include <QTimer>

class SunFlower : public AbstractPlant
{
    Q_OBJECT
public:
    SunFlower(int RowVal, int CulumnVal);
    ~SunFlower();
    
signals:
    void ProduceSun(int, int);
    
public slots:
    void Pause();
    void Restart();
    
private slots:
    void ProduceSunSlot();
    
private:
    QTimer *ProduceSunTimer;
    int leftmsec;
};

#endif // SUNFLOWER_H
