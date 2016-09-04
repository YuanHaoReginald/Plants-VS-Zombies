#ifndef SUNMANAGER_H
#define SUNMANAGER_H

#include <QObject>
#include <QTimer>
#include <QLabel>
#include "sun.h"

class SunManager : public QObject
{
    Q_OBJECT
public:
    explicit SunManager(QObject *parent = 0);
    ~SunManager();
    
    int getSunNumber();
    void Pause();
    void Restart();
    
signals:
    void UpAllSun();
    void PauseAllSun();
    void RestartAllSun();
    void DeleteAllSun();
    
private:
    int SunNumber;
    QTimer *MainManagerTimer;
    QLabel *showSunNum;
    bool isPause;
    int leftmsec;
    
public slots:
    void Start();
    
private slots:
    void GenerateSun();
    void FlowerSun(int, int);
    void AddSunNumber(int);
    void DeleteSun(Sun*);
    void MinusSunNumber(int);
};

#endif // SUNMANAGER_H
