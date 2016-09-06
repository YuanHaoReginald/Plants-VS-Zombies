#include "sunflower.h"
#include <QLabel>
#include <QPixmap>

SunFlower::SunFlower(int RowVal, int CulumnVal)
{
    m_Type = PlantType::SunFlower;
    Row = RowVal;
    Culumn = CulumnVal;
    blood = 6;
    width = 63;
    height = 72;
    PlantLabel = new QLabel(GlobalManager::CurrentWidget);
    PlantLabel->setGeometry(ForScale(GlobalManager::posX[Culumn] - 40 - width / 2), 
                            ForScale(GlobalManager::posY[Row] - 47 - height / 2),
                            ForScale(63), ForScale(72));
    PlantMovie = new QMovie(":/plant/res/images/plant/SunFlower/SunFlower1.gif");
    PlantMovie->setScaledSize(QSize(ForScale(63), ForScale(72)));
    PlantLabel->setMovie(PlantMovie);
    PlantMovie->start();
    
    ProduceSunTimer = new QTimer;
    ProduceSunTimer->setInterval(6000);
    connect(ProduceSunTimer, SIGNAL(timeout()), this, SLOT(ProduceSunSlot()));
    ProduceSunTimer->start();
}

SunFlower::~SunFlower()
{
    delete ProduceSunTimer;
}

void SunFlower::ProduceSunSlot()
{
    ProduceSunTimer->stop();
    ProduceSunTimer->setInterval(24000);
    emit ProduceSun(Row, Culumn, this);
}

void SunFlower::ReProduce()
{
    ProduceSunTimer->start();
}

void SunFlower::Pause()
{
    leftmsec = ProduceSunTimer->remainingTime();
    ProduceSunTimer->stop();
}

void SunFlower::Restart()
{
    ProduceSunTimer->setInterval(leftmsec);
    ProduceSunTimer->start();
}
