#include "sunflower.h"
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include "globalmanager.h"

SunFlower::SunFlower(int RowVal, int ColumnVal)
{
    ThisPlantType = PlantType::SunFlower;
    Row = RowVal;
    Column = ColumnVal;
    Blood = 6;
    Width = 63;
    Height = 72;
    PlantLabel = new QLabel(GlobalManager::CurrentWidget);
    PlantLabel->setMouseTracking(true);
    PlantLabel->show();
    PlantLabel->raise();
    PlantLabel->setGeometry(ForScale(GlobalManager::PosX[Column] - 40 - Width / 2), 
                            ForScale(GlobalManager::PosY[Row] - 47 - Height / 2),
                            ForScale(63), ForScale(72));
    PlantMovie = new QMovie(":/plant/res/images/plant/SunFlower/SunFlower1.gif");
    PlantMovie->setScaledSize(QSize(ForScale(63), ForScale(72)));
    PlantLabel->setMovie(PlantMovie);
    PlantMovie->start();
    
    ProduceSunTimer = new QTimer;
    ProduceSunTimer->setInterval(24000);
    connect(ProduceSunTimer, SIGNAL(timeout()), this, SLOT(ProduceSunSlot()));
    QTimer::singleShot(6000, this, SLOT(ProduceSunSlot()));
}

SunFlower::~SunFlower()
{
    delete ProduceSunTimer;
}

void SunFlower::ProduceSunSlot()
{
    if(!(ProduceSunTimer->isActive()))
        ProduceSunTimer->start();
    emit ProduceSun(Row, Column);
}
