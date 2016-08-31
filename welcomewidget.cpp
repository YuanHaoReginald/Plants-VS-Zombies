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
    ExitMainWidget.load(":/surface/res/images/surface/ExitMainWidgetBig.png");
    ExitMainWidget = ExitMainWidget.scaled(ForScale(GlobalManager::StanradWindowWidth), 
                                           ForScale(GlobalManager::StanradWindowWHeight), 
                                           Qt::KeepAspectRatio);
    OKButtonLabel = nullptr;
    CancelButtonLabel = nullptr;
    OKButtonNormal.load(":/surface/res/images/surface/OKButtonNormal.png");
    OKButtonNormal = OKButtonNormal.scaled(ForScale(163), ForScale(46));
    OKButtonHighlight.load(":/surface/res/images/surface/OKButtonHighlight.png");
    OKButtonHighlight = OKButtonHighlight.scaled(ForScale(163), ForScale(46));
    CancelButtonNormal.load(":/surface/res/images/surface/CancelButtonNormal.png");
    CancelButtonNormal = CancelButtonNormal.scaled(ForScale(163), ForScale(46));
    CancelButtonHighlight.load(":/surface/res/images/surface/CancelButtonHighlight.png");
    CancelButtonHighlight = CancelButtonHighlight.scaled(ForScale(163), ForScale(46));
    
    CurrentPointArea = BackgroundArea::NullArea;
    CurrentWelcomeStatus = WelcomeStatus::Normal;
    
    BackgroundLabel = new QLabel(this);
    BackgroundLabel->installEventFilter(this);
    BackgroundLabel->setGeometry(0, 0, ForScale(GlobalManager::StanradWindowWidth), 
                                 ForScale(GlobalManager::StanradWindowWHeight));
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
    switch(CurrentWelcomeStatus)
    {
    case WelcomeStatus::Normal:
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
                            CurrentWelcomeStatus = WelcomeStatus::Exit;
                            ExitMainWidgetLabel = new QLabel(this);
                            ExitMainWidgetLabel->setGeometry(0, 0, ForScale(GlobalManager::StanradWindowWidth), 
                                                             ForScale(GlobalManager::StanradWindowWHeight));
                            ExitMainWidgetLabel->setPixmap(ExitMainWidget);
                            OKButtonLabel = new QLabel(this);
                            OKButtonLabel->installEventFilter(this);
                            OKButtonLabel->setGeometry(ForScale(282), ForScale(364), ForScale(163), ForScale(46));
                            OKButtonLabel->setPixmap(OKButtonNormal);
                            CancelButtonLabel = new QLabel(this);
                            CancelButtonLabel->installEventFilter(this);
                            CancelButtonLabel->setGeometry(ForScale(445), ForScale(364), ForScale(163), ForScale(46));
                            CancelButtonLabel->setPixmap(CancelButtonNormal);
                            ExitMainWidgetLabel->show();
                            OKButtonLabel->show();
                            CancelButtonLabel->show();
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
        break;
    case WelcomeStatus::Exit:
        if(obj == OKButtonLabel)
        {
            if(event->type() == QEvent::Enter)
            {
                switch (CurrentPointArea) 
                {
                case BackgroundArea::NullArea:
                    OKButtonLabel->setPixmap(OKButtonHighlight);
                    setCursor(Qt::PointingHandCursor);
                    break;
                case BackgroundArea::ExitOkArea:
                    OKButtonLabel->setPixmap(OKButtonHighlight);
                    setCursor(Qt::PointingHandCursor);
                    break;
                default:
                    break;
                }
                return true;
            }
            else if(event->type() == QEvent::Leave)
            {
                switch (CurrentPointArea)
                {
                case BackgroundArea::NullArea:
                    OKButtonLabel->setPixmap(OKButtonNormal);
                    setCursor(Qt::ArrowCursor);
                    break;
                case BackgroundArea::ExitOkArea:
                    OKButtonLabel->setPixmap(OKButtonNormal);
                    setCursor(Qt::ArrowCursor);
                    break;
                default:
                    break;
                }
                return true;
            }
            else if(event->type() == QEvent::MouseButtonPress)
            {
                CurrentPointArea = BackgroundArea::ExitOkArea;
                return true;
            }
            else if(event->type() == QEvent::MouseButtonRelease)
            {
                if(CurrentPointArea == BackgroundArea::ExitOkArea)
                    qApp->quit();
                return true;
            }
            return false;
        }
        else if(obj == CancelButtonLabel)
        {
            
        }
        break;
    default:
        break;
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

bool WelcomeWidget::InArea(BackgroundArea currentArea, int _x, int _y)
{
    switch(currentArea)
    {
    case BackgroundArea::ExitArea:
        if(_x >= (ForScale(811)) && _x <= (ForScale(864)) && _y >= (ForScale(518)) && _y <= (ForScale(538)))
            return true;
        else
            return false;
        break;
    case BackgroundArea::HelpArea:
        if(_x >= (ForScale(730)) && _x <= (ForScale(784)) && _y >= (ForScale(528)) && _y <= (ForScale(548)))
            return true;
        else
            return false;
        break;
    case BackgroundArea::OptionArea:
        if(_x >= (ForScale(649)) && _x <= (ForScale(715)) && _y >= (ForScale(493)) && _y <= (ForScale(517)))
            return true;
        else
            return false;
        break;
    default:
        break;
    }
    return false;
}
