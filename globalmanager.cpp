#include "globalmanager.h"
#include <QApplication>
#include <QDesktopWidget>

double GlobalManager::DesktopScale = 1;
double GlobalManager::StanradWindowWidth = 900;
double GlobalManager::StanradWindowHeight = 600;
bool GlobalManager::EffectOn = true;
bool GlobalManager::MusicOn = true;
int GlobalManager::PosX[10] = {140, 220, 300, 380, 460, 540, 620, 700, 780, 860};
int GlobalManager::PosY[6] = {89, 183, 277, 371, 465, 559};
QWidget* GlobalManager::CurrentWidget = nullptr;
int GlobalManager::SunNumber = 100;
int GlobalManager::ZombieOrder[150] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                       1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 
                                       1, 1, 2, 1, 1, 1, 1, 1, 2, 1,
                                       1, 1, 2, 1, 2, 1, 2, 3, 1, 1, 
                                       1, 2, 2, 1, 3, 1, 2, 2, 3, 1,
                                       2, 2, 1, 3, 2, 2, 2, 1, 2, 3,
                                       1, 2, 1, 2, 1, 2, 2, 2, 3, 3,
                                       1, 2, 1, 2, 3, 3, 3, 1, 2, 3, 
                                       1, 2, 2, 3, 2, 1, 2, 3, 3, 2, 
                                       1, 2, 2, 3, 2, 1, 2, 3, 3, 2,
                                       1, 2, 2, 3, 2, 1, 2, 3, 3, 2, 
                                       1, 2, 2, 3, 2, 1, 2, 3, 3, 2,
                                       1, 2, 2, 1, 3, 3, 2, 2, 2, 3,
                                       1, 2, 2, 2, 3, 3, 3, 2, 2, 1,
                                       1, 2, 2, 3, 3, 3, 3, 2, 2, 2};

void initGlobalManager()
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    double DesktopWidth = desktopWidget->width();
    double DesktopHeight = desktopWidget->height();
    double ScaleTemp = DesktopWidth / DesktopHeight;
    const double MinDesktopWidth = 1280;
    const double MinDesktopHeight = 800;
    double StandradScale = MinDesktopHeight / MinDesktopWidth;
    GlobalManager::DesktopScale = (ScaleTemp >= StandradScale) ? (DesktopHeight / MinDesktopHeight) 
                                                               : (DesktopWidth / MinDesktopWidth);
}
