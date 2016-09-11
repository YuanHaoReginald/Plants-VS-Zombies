#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "abstractplant.h"

class Peashooter : public AbstractPlant
{
    Q_OBJECT
public:
    Peashooter(int RowVal, int ColumnVal);
    ~Peashooter();
    
signals:
    void EmitPea(int, int);
    
public slots:
    void StartEmitPea();
    void StopEmitPea();
    
private slots:
    void EmitPeaSlot();
    
private:
    QTimer *EmitPeaTimer;
};

#endif // PEASHOOTER_H
