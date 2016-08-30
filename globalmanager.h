#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H


class GlobalManager
{
private:
    GlobalManager();
    
public:
    static double DesktopScale;
    static double StanradWindowWidth;
    static double StanradWindowWHeight;
};

extern void initDesktopScale();
double ForScale(double temp);

enum class GameStatus { Welcome, Exit };

#endif // GLOBALMANAGER_H
