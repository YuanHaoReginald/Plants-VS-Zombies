#include "welcomewidget.h"
#include "globalmanager.h"
#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>

WelcomeWidget::WelcomeWidget(QWidget *parent = 0) : AbstractWidget(parent)
{
    setFixedWidth(GlobalManager::StanradWindowWidth * GlobalManager::DesktopScale);
    setFixedHeight(GlobalManager::StanradWindowWHeight * GlobalManager::DesktopScale);
    
    //ExitMainWindowLabel = nullptr;
    //ExitMainWindow = nullptr;
    
    CurrentPointArea = BackgroundArea::NullArea;
    
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
            switch (CurrentPointArea) 
            {
            case BackgroundArea::NullArea:
                if(InArea(BackgroundArea::ExitArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    SwitchBackground(Background::Exit);
                else if(InArea(BackgroundArea::HelpArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    SwitchBackground(Background::Help);
                else if(InArea(BackgroundArea::OptionArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    SwitchBackground(Background::Option);
                else
                    SwitchBackground(Background::Default);
                break;
            case BackgroundArea::OtherArea:
                SwitchBackground(Background::Default);
                break;
            case BackgroundArea::ExitArea:
                SwitchBackground(Background::Exit);
                break;
            case BackgroundArea::HelpArea:
                SwitchBackground(Background::Help);
                break;
            case BackgroundArea::OptionArea:
                SwitchBackground(Background::Option);
                break;
            default:
                break;
            }
            return true;
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *m_QMouseEvent = static_cast<QMouseEvent*>(event);
            if(m_QMouseEvent->button() == Qt::MouseButton::LeftButton)
            {
                if(InArea(BackgroundArea::ExitArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    CurrentPointArea = BackgroundArea::ExitArea;
                    SwitchBackground(Background::Exit);
                }
                else if(InArea(BackgroundArea::HelpArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    CurrentPointArea = BackgroundArea::HelpArea;
                    SwitchBackground(Background::Help);
                }
                else if(InArea(BackgroundArea::OptionArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    CurrentPointArea = BackgroundArea::OptionArea;
                    SwitchBackground(Background::Option);
                }
                else
                {
                    CurrentPointArea = BackgroundArea::OtherArea;
                    SwitchBackground(Background::Default);
                }
                return true;
            }
            return false;
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent *m_QMouseEvent = static_cast<QMouseEvent*>(event);
            if(m_QMouseEvent->button() == Qt::MouseButton::LeftButton)
            {
                switch(CurrentPointArea)
                {
                case BackgroundArea::ExitArea:
                    if(InArea(BackgroundArea::ExitArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    {
                        // to do something
                    }
                    break;
                case BackgroundArea::HelpArea:
                    if(InArea(BackgroundArea::HelpArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    {
                        // to do something
                    }
                    break;
                case BackgroundArea::OptionArea:
                    if(InArea(BackgroundArea::OptionArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    {
                        // to do something
                    }
                    break;
                default:
                    break;
                }
                CurrentPointArea = BackgroundArea::NullArea;
                SwitchBackground(Background::Default);
                return true;
            }
            return false;
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
        break;
    case Background::Help:
        CurrentBackground->load(":/surface/res/images/surface/SurfaceHelp.png");
        break;
    case Background::Option:
        CurrentBackground->load(":/surface/res/images/surface/SurfaceOption.png");
        break;
    default:
        break;
    }
    *CurrentBackground = CurrentBackground->scaled(GlobalManager::StanradWindowWidth * GlobalManager::DesktopScale, 
                          GlobalManager::StanradWindowWHeight * GlobalManager::DesktopScale, 
                          Qt::KeepAspectRatio);
    BackgroundLabel->setPixmap(*CurrentBackground);
}

bool WelcomeWidget::InArea(BackgroundArea currentArea, int _x, int _y)
{
    switch(currentArea)
    {
    case BackgroundArea::ExitArea:
        if(_x >= (811 * GlobalManager::DesktopScale)
                && _x <= (864 * GlobalManager::DesktopScale)
                && _y >= (518 * GlobalManager::DesktopScale)
                && _y <= (538 * GlobalManager::DesktopScale))
            return true;
        else
            return false;
        break;
    case BackgroundArea::HelpArea:
        if(_x >= (730 * GlobalManager::DesktopScale)
                && _x <= (784 * GlobalManager::DesktopScale)
                && _y >= (528 * GlobalManager::DesktopScale)
                && _y <= (548 * GlobalManager::DesktopScale))
            return true;
        else
            return false;
        break;
    case BackgroundArea::OptionArea:
        if(_x >= (649 * GlobalManager::DesktopScale)
                && _x <= (715 * GlobalManager::DesktopScale)
                && _y >= (493 * GlobalManager::DesktopScale)
                && _y <= (517 * GlobalManager::DesktopScale))
            return true;
        else
            return false;
        break;
    default:
        break;
    }
    return false;
}
