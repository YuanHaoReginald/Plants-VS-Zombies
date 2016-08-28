#include "welcomewidget.h"
#include "globalmanager.h"
#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>

WelcomeWidget::WelcomeWidget(QWidget *parent = 0) : AbstractWidget(parent)
{
    setFixedWidth(GlobalManager::StanradWindowWidth * GlobalManager::DesktopScale);
    setFixedHeight(GlobalManager::StanradWindowWHeight * GlobalManager::DesktopScale);
    
    BackgroundLabel = new QLabel(this);
    BackgroundLabel->installEventFilter(this);
    BackgroundLabel->setGeometry(0, 0, GlobalManager::StanradWindowWidth * GlobalManager::DesktopScale, 
                                 GlobalManager::StanradWindowWHeight * GlobalManager::DesktopScale);
    BackgroundStatus = Background::Exit;
    CurrentBackground = nullptr;
    SwitchBackground(Background::Default);
    BackgroundLabel->setMouseTracking(true);
}

WelcomeWidget::~WelcomeWidget()
{
    delete BackgroundLabel;
    delete CurrentBackground;
}

bool WelcomeWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == BackgroundLabel)
    {
        if(event->type() == QEvent::MouseMove)
        {
            QMouseEvent *m_QMouseEvent = static_cast<QMouseEvent*>(event);
            if(m_QMouseEvent->x() >= (811 * GlobalManager::DesktopScale)
                    && m_QMouseEvent->x() <= (864 * GlobalManager::DesktopScale)
                    && m_QMouseEvent->y() >= (518 * GlobalManager::DesktopScale)
                    && m_QMouseEvent->y() <= (538 * GlobalManager::DesktopScale))
            {
                SwitchBackground(Background::Exit);
                return true;
            }
            else
            {
                SwitchBackground(Background::Default);
                return true;
            }
        }
        return false;
    }
    return WelcomeWidget::eventFilter(obj, event);
}

void WelcomeWidget::SwitchBackground(Background background)
{
    if(BackgroundStatus == background)
        return;
    BackgroundStatus = background;
    delete CurrentBackground;
    
    CurrentBackground = new QPixmap;
    switch (BackgroundStatus) 
    {
    case Background::Default:
        CurrentBackground->load(":/surface/res/images/surface/WelcomeSurfaceBackground.png");
        break;
    case Background::Exit:
        CurrentBackground->load(":/surface/res/images/surface/SurfaceExit.png");
    default:
        break;
    }
    *CurrentBackground = CurrentBackground->scaled(GlobalManager::StanradWindowWidth * GlobalManager::DesktopScale, 
                          GlobalManager::StanradWindowWHeight * GlobalManager::DesktopScale, 
                          Qt::KeepAspectRatio);
    BackgroundLabel->setPixmap(*CurrentBackground);
}
