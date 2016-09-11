#include "wallnut.h"
#include "enumlist.h"
#include "globalmanager.h"

WallNut::WallNut(int RowVal, int ColumnVal)
{
    ThisPlantType = PlantType::WallNut;
    Row = RowVal;
    Column = ColumnVal;
    Blood = 72;
    Width = 61;
    Height = 71;
    PlantLabel = new QLabel(GlobalManager::CurrentWidget);
    PlantLabel->setMouseTracking(true);
    PlantLabel->show();
    PlantLabel->raise();
    PlantLabel->setGeometry(ForScale(GlobalManager::PosX[Column] - 40 - Width / 2), 
                            ForScale(GlobalManager::PosY[Row] - 47 - Height / 2),
                            ForScale(Width), ForScale(Height));
    PlantMovie = new QMovie(":/plant/res/images/plant/WallNut/WallNut.gif");
    PlantMovie->setScaledSize(QSize(ForScale(Width), ForScale(Height)));
    PlantLabel->setMovie(PlantMovie);
    PlantMovie->start();
    
    CurrentStatus = WallNutStatus::Normal;
}

void WallNut::getAttack()
{
    Blood--;
    CheckStatus();
    if(Blood == 0)
        emit die(this);
}

void WallNut::CheckStatus()
{
    if(Blood <= 48 && Blood >= 25 && CurrentStatus != WallNutStatus::Crash1)
    {
        delete PlantMovie;
        PlantMovie = new QMovie(":/plant/res/images/plant/WallNut/Wallnut_cracked1.gif");
        PlantMovie->setScaledSize(QSize(ForScale(Width), ForScale(Height)));
        PlantLabel->setMovie(PlantMovie);
        PlantMovie->start();
        CurrentStatus = WallNutStatus::Crash1;
    }
    else if(Blood <= 24 && CurrentStatus != WallNutStatus::Crash2)
    {
        delete PlantMovie;
        PlantMovie = new QMovie(":/plant/res/images/plant/WallNut/Wallnut_cracked2.gif");
        PlantMovie->setScaledSize(QSize(ForScale(Width), ForScale(Height)));
        PlantLabel->setMovie(PlantMovie);
        PlantMovie->start();
        CurrentStatus = WallNutStatus::Crash2;
    }
}
