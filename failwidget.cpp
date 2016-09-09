#include "enumlist.h"
#include "failwidget.h"
#include "globalmanager.h"

FailWidget::FailWidget(QWidget* parent) : AbstractWidget(parent)
{
    FailLabel = new QLabel(this);
    FailLabel->setMouseTracking(true);
    FailPixmap = new QPixmap(":/surface/res/images/surface/Fail.png");
    *FailPixmap = FailPixmap->scaled(ForScale(GlobalManager::StanradWindowWidth),
                                   ForScale(GlobalManager::StanradWindowWHeight));
    FailLabel->resize(ForScale(GlobalManager::StanradWindowWidth),
                     ForScale(GlobalManager::StanradWindowWHeight));
    FailLabel->move(0, 0);
    FailLabel->setPixmap(FailPixmap);
    FailLabel->show();
}

FailWidget::~FailWidget()
{
    delete FailLabel;
    delete FailPixmap;
}

void FailWidget::mousePressEvent()
{
    emit StatusChanged(GameStatus::Welcome);
}
