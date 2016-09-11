#include "pea.h"
#include "globalmanager.h"

Pea::Pea(int RowVal, int ColumnVal, QObject *parent) : QObject(parent)
{
    Width = Height = 24;
    PosX = GlobalManager::PosX[ColumnVal] - 18;
    PosY = GlobalManager::PosY[RowVal - 1] + 17;
    
    PeaPixmap = new QPixmap(":/plant/res/images/plant/pea.png");
    *PeaPixmap = PeaPixmap->scaled(ForScale(Width), ForScale(Height));
    PeaLabel = new QLabel(GlobalManager::CurrentWidget);
    PeaLabel->setMouseTracking(true);
    PeaLabel->setPixmap(*PeaPixmap);
    PeaLabel->setGeometry(ForScale(PosX), ForScale(PosY), ForScale(Width), ForScale(Height));
    PeaLabel->show();
    PeaLabel->raise();
}

Pea::~Pea()
{
    delete PeaLabel;
    delete PeaPixmap;
}

void Pea::PeaMove()
{
    PosX += 2;
    PeaLabel->move(ForScale(PosX), ForScale(PosY));
}
