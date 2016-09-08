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
    
    int getWidth();
    int getX();
    
signals:
    void die(Pea*);
    
public slots:
    void Pause();
    void Restart();
    void PeaMove();
    
private:
    QLabel *PeaLabel;
    QPixmap *PeaPixmap;
    
    int width, height, xVal, yVal;
};

#endif // PEA_H
