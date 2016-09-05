#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H
#include <QWidget>

enum class GameStatus { Welcome, Advence, Mini, IQ };
enum class PlantType { SunFlower, WallNut, Peashooter, Chomper };
enum class CardStatus { Normal, Disable, Freezed };

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
};

extern void initGlobalManager();
double ForScale(double temp);

#endif // GLOBALMANAGER_H
