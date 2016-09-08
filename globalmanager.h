#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H
#include <QWidget>
#include "enumlist.h"

class GlobalManager
{
private:
    GlobalManager();
    
public:
    static double DesktopScale;
    static double StanradWindowWidth;
    static double StanradWindowWHeight;
    static bool MusicOn;
    static bool EffectOn;
    static int posX[10];
    static int posY[6];
    static QWidget* CurrentWidget;
    static int NumberOfSun;
    static int ZombieLine[150];
};

extern void initGlobalManager();
double ForScale(double temp);

#endif // GLOBALMANAGER_H
