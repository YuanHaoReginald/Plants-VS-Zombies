#include "wallnut.h"
#include "enumlist.h"
#include "globalmanager.h"

WallNut::WallNut(int RowVal, int CulumnVal)
{
    m_Type = PlantType::WallNut;
    Row = RowVal;
    Culumn = CulumnVal;
    blood = 72;
    width = 61;
    height = 71;
    PlantLabel = new QLabel(GlobalManager::CurrentWidget);
    PlantLabel->setMouseTracking(true);
    PlantLabel->show();
    PlantLabel->raise();
    PlantLabel->setGeometry(ForScale(GlobalManager::posX[Culumn] - 40 - width / 2), 
                            ForScale(GlobalManager::posY[Row] - 47 - height / 2),
                            ForScale(width), ForScale(height));
    PlantMovie = new QMovie(":/plant/res/images/plant/WallNut/WallNut.gif");
    PlantMovie->setScaledSize(QSize(ForScale(width), ForScale(height)));
    PlantLabel->setMovie(PlantMovie);
    PlantMovie->start();
    
    CurrentStatus = WallNutStatus::Normal;
}

WallNut::~WallNut()
{
    
}

void WallNut::getAttack()
{
    blood--;
    checkStatus();
    if(blood == 0)
        emit die(this);
}

void WallNut::checkStatus()
{
    if(blood <= 48 && blood >= 25 && CurrentStatus != WallNutStatus::Crash1)
    {
        delete PlantMovie;
        PlantMovie = new QMovie(":/plant/res/images/plant/WallNut/Wallnut_cracked1.gif");
        PlantMovie->setScaledSize(QSize(ForScale(width), ForScale(height)));
        PlantLabel->setMovie(PlantMovie);
        PlantMovie->start();
        CurrentStatus = WallNutStatus::Crash1;
    }
    else if(blood <= 24 && CurrentStatus != WallNutStatus::Crash2)
    {
        delete PlantMovie;
        PlantMovie = new QMovie(":/plant/res/images/plant/WallNut/Wallnut_cracked2.gif");
        PlantMovie->setScaledSize(QSize(ForScale(width), ForScale(height)));
        PlantLabel->setMovie(PlantMovie);
        PlantMovie->start();
        CurrentStatus = WallNutStatus::Crash1;
    }
}
