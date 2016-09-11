#include "peashooter.h"
#include "globalmanager.h"
#include <QLabel>
#include <QMovie>
#include <QTimer>

Peashooter::Peashooter(int RowVal, int ColumnVal)
{
    ThisPlantType = PlantType::Peashooter;
    Row = RowVal;
    Column = ColumnVal;
    Blood = 6;
    Width = 62;
    Height = 70;
    PlantLabel = new QLabel(GlobalManager::CurrentWidget);
    PlantLabel->setMouseTracking(true);
    PlantLabel->show();
    PlantLabel->raise();
    PlantLabel->setGeometry(ForScale(GlobalManager::PosX[Column] - 40 - Width / 2), 
                            ForScale(GlobalManager::PosY[Row] - 47 - Height / 2),
                            ForScale(Width), ForScale(Height));
    PlantMovie = new QMovie(":/plant/res/images/plant/Peashooter/Peashooter.gif");
    PlantMovie->setScaledSize(QSize(ForScale(Width), ForScale(Height)));
    PlantMovie->setSpeed(80);
    PlantLabel->setMovie(PlantMovie);
    PlantMovie->start();
    
    EmitPeaTimer = new QTimer;
    EmitPeaTimer->setInterval(1500);
    connect(EmitPeaTimer, SIGNAL(timeout()), this, SLOT(EmitPeaSlot()));
}

Peashooter::~Peashooter()
{
    delete EmitPeaTimer;
}

void Peashooter::EmitPeaSlot()
{
    emit EmitPea(Row, Column);
}

void Peashooter::StartEmitPea()
{
    if(EmitPeaTimer->isActive())
        return;
    EmitPeaTimer->start();    
}

void Peashooter::StopEmitPea()
{
    EmitPeaTimer->stop();
}
