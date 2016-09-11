#ifndef PEA_H
#define PEA_H

#include <QObject>
#include <QLabel>
#include <QPixmap>

class Pea : public QObject
{
    Q_OBJECT
public:
    explicit Pea(int, int, QObject *parent = 0);
    ~Pea();
    
    int getWidth() const { return Width; }
    int getPosX() const { return PosX; }
    
public slots:
    void PeaMove();
    
private:
    QLabel *PeaLabel;
    QPixmap *PeaPixmap;
    
    int Width, Height, PosX, PosY;
};

#endif // PEA_H
