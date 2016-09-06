#ifndef SUNMANAGER_H
#define SUNMANAGER_H

#include <QObject>
#include <QTimer>
#include <QLabel>
#include "sun.h"
#include "sunflower.h"

class SunManager : public QObject
{
    Q_OBJECT
public:
    explicit SunManager(QObject *parent = 0);
    ~SunManager();
    
    void Pause();
    void Restart();
    
signals:
    void UpAllSun();
    void PauseAllSun();
    void RestartAllSun();
    void DeleteAllSun();
    void SunNumberUpdate();
    
private:
    QTimer *MainManagerTimer;
    QLabel *showSunNum;
    bool isPause;
    int leftmsec;
    
public slots:
    void Start();
    void FlowerSun(int, int, SunFlower*);
    
private slots:
    void GenerateSun();
    void AddSunNumber(int);
    void DeleteSun(Sun*);
    void MinusSunNumber(int);
};

#endif // SUNMANAGER_H
