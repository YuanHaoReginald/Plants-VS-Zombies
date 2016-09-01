#include "globalmanager.h"
#include <QApplication>
#include <QDesktopWidget>

GlobalManager::GlobalManager()
{
    
}

double GlobalManager::DesktopScale = 1;
double GlobalManager::StanradWindowWidth = 900;
double GlobalManager::StanradWindowWHeight = 600;
bool GlobalManager::EffectOn = true;
bool GlobalManager::MusicOn = true;

void initDesktopScale()
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    double DesktopWidth = desktopWidget->width();
    double DesktopHeight = desktopWidget->height();
    double ScaleTemp = DesktopWidth / DesktopHeight;
    const double MinDesktopWidth = 1280;
    const double MinDesktopHeight = 800;
    double StandradScale = MinDesktopHeight / MinDesktopWidth;
    if(ScaleTemp >= StandradScale)
        GlobalManager::DesktopScale = DesktopHeight / MinDesktopHeight;
    else if(ScaleTemp < StandradScale)
        GlobalManager::DesktopScale = DesktopWidth / MinDesktopWidth;
}

double ForScale(double temp)
{
    return (temp * GlobalManager::DesktopScale);
}
