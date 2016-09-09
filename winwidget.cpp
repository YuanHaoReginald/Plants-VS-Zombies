#include "enumlist.h"
#include "winwidget.h"
#include "globalmanager.h"

WinWidget::WinWidget(QWidget* parent) : AbstractWidget(parent)
{
    WinLabel = new QLabel(this);
    WinLabel->setMouseTracking(true);
    WinPixmap = new QPixmap(":/surface/res/images/surface/Win.png");
    *WinPixmap = WinPixmap->scaled(ForScale(GlobalManager::StanradWindowWidth),
                                   ForScale(GlobalManager::StanradWindowWHeight));
    WinLabel->resize(ForScale(GlobalManager::StanradWindowWidth),
                     ForScale(GlobalManager::StanradWindowWHeight));
    WinLabel->move(0, 0);
    WinLabel->setPixmap(WinPixmap);
    WinLabel->show();
}

WinWidget::~WinWidget()
{
    delete WinLabel;
    delete WinPixmap;
}

void WinWidget::mousePressEvent()
{
    emit StatusChanged(GameStatus::Welcome);
}
