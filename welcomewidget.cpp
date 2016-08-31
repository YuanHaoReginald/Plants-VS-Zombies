#include "welcomewidget.h"
#include "globalmanager.h"
#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>
#include <qapplication.h>

WelcomeWidget::WelcomeWidget(QWidget *parent = 0) : AbstractWidget(parent)
{
    setFixedWidth(ForScale(GlobalManager::StanradWindowWidth));
    setFixedHeight(ForScale(GlobalManager::StanradWindowWHeight));
    
    ExitMainWidgetLabel = nullptr;
    ExitMainWidget = nullptr;
    CurrentExitStatus = ExitStatus::NotExit;
    
    CurrentPointArea = BackgroundArea::NullArea;
    
    BackgroundLabel = new QLabel(this);
    BackgroundLabel->installEventFilter(this);
    BackgroundLabel->setGeometry(0, 0, ForScale(GlobalManager::StanradWindowWidth), 
                                 ForScale(GlobalManager::StanradWindowWHeight));
    BackgroundStatus = Background::NoBackGround;
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
                {
                    SwitchBackground(Background::Exit);
                    setCursor(Qt::PointingHandCursor);
                }
                else if(InArea(BackgroundArea::HelpArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    SwitchBackground(Background::Help);
                    setCursor(Qt::PointingHandCursor);
                }
                else if(InArea(BackgroundArea::OptionArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    SwitchBackground(Background::Option);
                    setCursor(Qt::PointingHandCursor);
                }
                else
                {
                    SwitchBackground(Background::Default);
                    setCursor(Qt::ArrowCursor);
                }
                break;
            case BackgroundArea::OtherArea:
                SwitchBackground(Background::Default);
                break;
            case BackgroundArea::ExitArea:
                SwitchBackground(Background::Exit);
                if(InArea(BackgroundArea::ExitArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    setCursor(Qt::PointingHandCursor);
                else
                    setCursor(Qt::ArrowCursor);
                break;
            case BackgroundArea::HelpArea:
                SwitchBackground(Background::Help);
                if(InArea(BackgroundArea::HelpArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    setCursor(Qt::PointingHandCursor);
                else
                    setCursor(Qt::ArrowCursor);
                break;
            case BackgroundArea::OptionArea:
                SwitchBackground(Background::Option);
                if(InArea(BackgroundArea::OptionArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    setCursor(Qt::PointingHandCursor);
                else
                    setCursor(Qt::ArrowCursor);
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
                    CurrentPointArea = BackgroundArea::ExitArea;
                else if(InArea(BackgroundArea::HelpArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    CurrentPointArea = BackgroundArea::HelpArea;
                else if(InArea(BackgroundArea::OptionArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    CurrentPointArea = BackgroundArea::OptionArea;
                else
                    CurrentPointArea = BackgroundArea::OtherArea;
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
                        ExitMainWidgetLabel = new QLabel(this);
                        ExitMainWidgetLabel->installEventFilter(this);
                        ExitMainWidgetLabel->setMouseTracking(true);
                        ExitMainWidgetLabel->setGeometry(0, 0, ForScale(GlobalManager::StanradWindowWidth), 
                                                         ForScale(GlobalManager::StanradWindowWHeight));
                        SwitchExitStatus(ExitStatus::ExitNormal);
                        ExitMainWidgetLabel->show();
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
                setCursor(Qt::ArrowCursor);
                CurrentPointArea = BackgroundArea::NullArea;
                SwitchBackground(Background::Default);
                return true;
            }
            return false;
        }
        return false;
    }
    else if(obj == ExitMainWidgetLabel)
    {
        if(event->type() == QEvent::MouseMove)
        {
            QMouseEvent *m_QMouseEvent = static_cast<QMouseEvent*>(event);            
            switch (CurrentPointArea) 
            {
            case BackgroundArea::NullArea:
                if(InArea(BackgroundArea::ExitOKArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    SwitchExitStatus(ExitStatus::ExitOK);
                    setCursor(Qt::PointingHandCursor);
                }
                else if(InArea(BackgroundArea::ExitCancelArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    SwitchExitStatus(ExitStatus::ExitCancel);
                    setCursor(Qt::PointingHandCursor);
                }
                else
                {
                    SwitchExitStatus(ExitStatus::ExitNormal);
                    setCursor(Qt::ArrowCursor);
                }
                break;
            case BackgroundArea::OtherArea:
                SwitchExitStatus(ExitStatus::ExitNormal);
                break;
            case BackgroundArea::ExitOKArea:
                if(InArea(BackgroundArea::ExitOKArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    SwitchExitStatus(ExitStatus::ExitOK);                    
                    setCursor(Qt::PointingHandCursor);
                }
                else
                {
                    SwitchExitStatus(ExitStatus::ExitNormal);                    
                    setCursor(Qt::ArrowCursor);
                }
                break;
            case BackgroundArea::ExitCancelArea:
                if(InArea(BackgroundArea::ExitCancelArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    SwitchExitStatus(ExitStatus::ExitCancel);                    
                    setCursor(Qt::PointingHandCursor);
                }
                else
                {
                    SwitchExitStatus(ExitStatus::ExitNormal);                    
                    setCursor(Qt::ArrowCursor);
                }
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
                if(InArea(BackgroundArea::ExitOKArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    CurrentPointArea = BackgroundArea::ExitOKArea;
                else if(InArea(BackgroundArea::ExitCancelArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    CurrentPointArea = BackgroundArea::ExitCancelArea;
                else
                    CurrentPointArea = BackgroundArea::OtherArea;
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
                case BackgroundArea::ExitOKArea:
                    if(InArea(BackgroundArea::ExitOKArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                        qApp->quit();
                    break;
                case BackgroundArea::ExitCancelArea:
                    if(InArea(BackgroundArea::ExitCancelArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    {
                        delete ExitMainWidgetLabel;
                        delete ExitMainWidget;
                        ExitMainWidgetLabel = nullptr;
                        ExitMainWidget = nullptr;
                        setCursor(Qt::ArrowCursor);
                        CurrentPointArea = BackgroundArea::NullArea;
                        CurrentExitStatus = ExitStatus::NotExit;
                        return true;
                    }
                    break;
                default:
                    break;
                }
                setCursor(Qt::ArrowCursor);
                CurrentPointArea = BackgroundArea::NullArea;
                SwitchExitStatus(ExitStatus::ExitNormal);
                return true;
            }
            return false;
        }
        return false;        
    }
    return false;
    return AbstractWidget::eventFilter(obj, event);
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
    *CurrentBackground = CurrentBackground->scaled(ForScale(GlobalManager::StanradWindowWidth), 
                                                   ForScale(GlobalManager::StanradWindowWHeight), 
                                                   Qt::KeepAspectRatio);
    BackgroundLabel->setPixmap(*CurrentBackground);
}

void WelcomeWidget::SwitchExitStatus(ExitStatus temp)
{
    if(CurrentExitStatus == temp)
        return;
    CurrentExitStatus = temp;
    delete ExitMainWidget;
    
    ExitMainWidget = new QPixmap;
    switch (CurrentExitStatus) {
    case ExitStatus::ExitNormal:
        ExitMainWidget->load(":/surface/res/images/surface/ExitMainWidgetNormal.png");
        break;
    case ExitStatus::ExitOK:
        ExitMainWidget->load(":/surface/res/images/surface/ExitMainWidgetOK.png");
        break;
    case ExitStatus::ExitCancel:
        ExitMainWidget->load(":/surface/res/images/surface/ExitMainWidgetCancel.png");
    default:
        break;
    }
    *ExitMainWidget = ExitMainWidget->scaled(ForScale(GlobalManager::StanradWindowWidth),
                                             ForScale(GlobalManager::StanradWindowWHeight),
                                             Qt::KeepAspectRatio);
    ExitMainWidgetLabel->setPixmap(*ExitMainWidget);
}

bool WelcomeWidget::InArea(BackgroundArea currentArea, int _x, int _y)
{
    switch(currentArea)
    {
    case BackgroundArea::ExitArea:
        return ComparePosition(_x, _y, 811, 864, 518, 538);
        break;
    case BackgroundArea::HelpArea:
        return ComparePosition(_x, _y, 730, 784, 528, 548);
        break;
    case BackgroundArea::OptionArea:
        return ComparePosition(_x, _y, 649, 715, 493, 517);        
        break;
    case BackgroundArea::ExitOKArea:
        return ComparePosition(_x, _y, 282, 445, 364, 410);        
        break;
    case BackgroundArea::ExitCancelArea:
        return ComparePosition(_x, _y, 445, 608, 364, 410);
        break;
    default:
        break;
    }
    return false;
}

bool WelcomeWidget::ComparePosition(int _x, int _y, int xMin, int xMax, int yMin, int yMax)
{
    if(_x >= (ForScale(xMin)) && _x <= (ForScale(xMax)) && _y >= (ForScale(yMin)) && _y <= (ForScale(yMax)))
        return true;
    else
        return false;
}
