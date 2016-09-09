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
    PeaLabel->setMouseTracking(true);
    PeaLabel->setPixmap(*PeaPixmap);
    PeaLabel->setGeometry(ForScale(xVal), ForScale(yVal), ForScale(width), ForScale(height));
    PeaLabel->show();
    PeaLabel->raise();
}

Pea::~Pea()
{
    delete PeaLabel;
    delete PeaPixmap;
}

int Pea::getWidth()
{
    return width;
}

int Pea::getX()
{
    return xVal;
}

void Pea::PeaMove()
{
    xVal += 2;
    PeaLabel->move(ForScale(xVal), ForScale(yVal));
}
