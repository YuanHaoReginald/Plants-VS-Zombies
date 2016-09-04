#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H
#include <QWidget>


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
};

extern void initGlobalManager();
double ForScale(double temp);

enum class GameStatus { Welcome, Advence, Mini, IQ };

#endif // GLOBALMANAGER_H
