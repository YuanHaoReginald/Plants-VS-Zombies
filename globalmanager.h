#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H

#include <QWidget>
#include "enumlist.h"

class GlobalManager
{
private:
    GlobalManager() { }
    
public:
    static double DesktopScale;
    static double StanradWindowWidth;
    static double StanradWindowHeight;
    static bool MusicOn;
    static bool EffectOn;
    static int PosX[10];
    static int PosY[6];
    static QWidget* CurrentWidget;
    static int SunNumber;
    static int ZombieOrder[150];
};

extern void initGlobalManager();
inline double ForScale(double temp) { return (temp * GlobalManager::DesktopScale); }

#endif // GLOBALMANAGER_H
