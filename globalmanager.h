#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H


class GlobalManager
{
private:
    GlobalManager();
    
public:
    static double DesktopScale;
    static void initDesktopScale();
    static double StanradWindowWidth;
    static double StanradWindowWHeight;
};

#endif // GLOBALMANAGER_H
