#include "peashooter.h"
#include "globalmanager.h"
#include <QLabel>
#include <QMovie>
#include <QTimer>

Peashooter::Peashooter(int RowVal, int CulumnVal)
{
    m_Type = PlantType::Peashooter;
    Row = RowVal;
    Culumn = CulumnVal;
    blood = 6;
    width = 62;
    height = 70;
    PlantLabel = new QLabel(GlobalManager::CurrentWidget);
    PlantLabel->setMouseTracking(true);
    PlantLabel->show();
    PlantLabel->raise();
    PlantLabel->setGeometry(ForScale(GlobalManager::posX[Culumn] - 40 - width / 2), 
                            ForScale(GlobalManager::posY[Row] - 47 - height / 2),
                            ForScale(width), ForScale(height));
    PlantMovie = new QMovie(":/plant/res/images/plant/Peashooter/Peashooter.gif");
    PlantMovie->setScaledSize(QSize(ForScale(width), ForScale(height)));
    PlantLabel->setMovie(PlantMovie);
    PlantMovie->start();
    
    EmitPeaTimer = new QTimer;
    EmitPeaTimer->setInterval(1500);
    connect(EmitPeaTimer, SIGNAL(timeout()), this, SLOT(EmitPeaSlot()));
    EmitPeaTimer->start();
}

Peashooter::~Peashooter()
{
    delete EmitPeaTimer;
}

void Peashooter::EmitPeaSlot()
{
    EmitPeaTimer->stop();
    EmitPeaTimer->setInterval(1500);
    EmitPeaTimer->start();
    emit EmitPea(Row, Culumn);
}

void Peashooter::Pause()
{
    leftmsec = EmitPeaTimer->remainingTime();
    EmitPeaTimer->stop();
}

void Peashooter::Restart()
{
    EmitPeaTimer->setInterval(leftmsec);
    EmitPeaTimer->start();
}

