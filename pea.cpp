#include "pea.h"
#include "globalmanager.h"

Pea::Pea(int RowVal, int CulumnVal, QObject *parent) : QObject(parent)
{
    width = height = 24;
    xVal = GlobalManager::posX[CulumnVal] - 18;
    yVal = GlobalManager::posY[RowVal - 1] + 17;
    
    PeaPixmap = new QPixmap(":/plant/res/images/plant/pea.png");
    *PeaPixmap = PeaPixmap->scaled(ForScale(width), ForScale(height));
    PeaLabel = new QLabel(GlobalManager::CurrentWidget);
    PeaLabel->setPixmap(*PeaPixmap);
    PeaLabel->setGeometry(ForScale(xVal), ForScale(yVal), ForScale(width), ForScale(height));
    PeaLabel->show();
    PeaLabel->raise();
    
    PeaRunTimer = new QTimer;
    PeaRunTimer->setInterval(5);
    connect(PeaRunTimer, SIGNAL(timeout()), this, SLOT(RunSlot()));
    PeaRunTimer->start();
}

Pea::~Pea()
{
    delete PeaLabel;
    delete PeaPixmap;
    delete PeaRunTimer;
}

int Pea::getWidth()
{
    return width;
}

int Pea::getX()
{
    return xVal;
}

void Pea::RunSlot()
{
    xVal++;
    PeaLabel->move(ForScale(xVal), ForScale(yVal));
    if(xVal >= 900)
        emit die(this);
}

void Pea::Pause()
{
    PeaRunTimer->stop();
}

void Pea::Restart()
{
    PeaRunTimer->start();
}
