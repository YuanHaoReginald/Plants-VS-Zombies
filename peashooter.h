#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "abstractplant.h"

class Peashooter : public AbstractPlant
{
    Q_OBJECT
public:
    Peashooter(int RowVal, int CulumnVal);
    ~Peashooter();
    
signals:
    void EmitPea(int, int);
    
public slots:
    void Pause();
    void Restart();
    
private slots:
    void EmitPeaSlot();
    
private:
    QTimer *EmitPeaTimer;
    int leftmsec;
};

#endif // PEASHOOTER_H
