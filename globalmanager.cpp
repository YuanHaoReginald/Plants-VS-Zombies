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
int GlobalManager::posX[10] = {140, 220, 300, 380, 460, 540, 620, 700, 780, 860};
int GlobalManager::posY[6] = {89, 183, 277, 371, 465, 559};
QWidget* GlobalManager::CurrentWidget = nullptr;
int GlobalManager::NumberOfSun = 50;

void initGlobalManager()
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
