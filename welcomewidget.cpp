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
    ExitMainWidgetPixmap = nullptr;
    CurrentExitStatus = ExitStatus::NotExit;
    
    HelpWidgetLabel = nullptr;
    HelpWidgetPixmap = nullptr;
    CurrentHelpStatus = HelpStatus::NotHelp;
    
    MenuWidgetLabel = nullptr;
    MenuWidgetPixmap = nullptr;
    CurrentMenuStatus = MenuStatus::NotMenu;
    
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
                else if(InArea(BackgroundArea::AdvenceArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    SwitchBackground(Background::Advence);
                    setCursor(Qt::PointingHandCursor);
                }
                else if(InArea(BackgroundArea::MiniArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    SwitchBackground(Background::Mini);
                    setCursor(Qt::PointingHandCursor);
                }
                else if(InArea(BackgroundArea::IQArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    SwitchBackground(Background::IQ);
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
            case BackgroundArea::AdvenceArea:
                SwitchBackground(Background::Advence);
                if(InArea(BackgroundArea::AdvenceArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    setCursor(Qt::PointingHandCursor);
                else
                    setCursor(Qt::ArrowCursor);
                break;
            case BackgroundArea::MiniArea:
                SwitchBackground(Background::Mini);
                if(InArea(BackgroundArea::MiniArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    setCursor(Qt::PointingHandCursor);
                else
                    setCursor(Qt::ArrowCursor);
                break;
            case BackgroundArea::IQArea:
                SwitchBackground(Background::IQ);
                if(InArea(BackgroundArea::IQArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
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
                else if(InArea(BackgroundArea::AdvenceArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    CurrentPointArea = BackgroundArea::AdvenceArea;
                else if(InArea(BackgroundArea::MiniArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    CurrentPointArea = BackgroundArea::MiniArea;
                else if(InArea(BackgroundArea::IQArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    CurrentPointArea = BackgroundArea::IQArea;
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
                        HelpWidgetLabel = new QLabel(this);
                        HelpWidgetLabel->installEventFilter(this);
                        HelpWidgetLabel->setMouseTracking(true);
                        HelpWidgetLabel->setGeometry(0, 0, ForScale(GlobalManager::StanradWindowWidth), 
                                                         ForScale(GlobalManager::StanradWindowWHeight));
                        SwitchHelpStatus(HelpStatus::HelpNormal);
                        HelpWidgetLabel->show();
                    }
                    break;
                case BackgroundArea::OptionArea:
                    if(InArea(BackgroundArea::OptionArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    {
                        MenuWidgetLabel = new QLabel(this);
                        MenuWidgetLabel->installEventFilter(this);
                        MenuWidgetLabel->setMouseTracking(true);
                        MenuWidgetLabel->setGeometry(0, 0, ForScale(GlobalManager::StanradWindowWidth), 
                                                         ForScale(GlobalManager::StanradWindowWHeight));
                        SwitchMenuStatus(MenuStatus::MenuYYNormal);
                        MenuWidgetLabel->show();
                    }
                    break;
                case BackgroundArea::AdvenceArea:
                    if(InArea(BackgroundArea::AdvenceArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    {
                        // to do something
                    }
                    break;
                case BackgroundArea::MiniArea:
                    if(InArea(BackgroundArea::MiniArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    {
                        // to do something
                    }
                    break;
                case BackgroundArea::IQArea:
                    if(InArea(BackgroundArea::IQArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
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
                        delete ExitMainWidgetPixmap;
                        ExitMainWidgetLabel = nullptr;
                        ExitMainWidgetPixmap = nullptr;
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
    else if(obj == HelpWidgetLabel)
    {
        if(event->type() == QEvent::MouseMove)
        {
            QMouseEvent *m_QMouseEvent = static_cast<QMouseEvent*>(event);            
            switch (CurrentPointArea) 
            {
            case BackgroundArea::NullArea:
                if(InArea(BackgroundArea::HelpMainArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    SwitchHelpStatus(HelpStatus::HelpHighlight);
                    setCursor(Qt::PointingHandCursor);
                }
                else
                {
                    SwitchHelpStatus(HelpStatus::HelpNormal);
                    setCursor(Qt::ArrowCursor);
                }
                break;
            case BackgroundArea::OtherArea:
                SwitchHelpStatus(HelpStatus::HelpNormal);
                break;
            case BackgroundArea::HelpMainArea:
                if(InArea(BackgroundArea::HelpMainArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    SwitchHelpStatus(HelpStatus::HelpHighlight);                    
                    setCursor(Qt::PointingHandCursor);
                }
                else
                {
                    SwitchHelpStatus(HelpStatus::HelpNormal);                    
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
                if(InArea(BackgroundArea::HelpMainArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    CurrentPointArea = BackgroundArea::HelpMainArea;
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
                case BackgroundArea::HelpMainArea:
                    if(InArea(BackgroundArea::HelpMainArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    {
                        delete HelpWidgetLabel;
                        delete HelpWidgetPixmap;
                        HelpWidgetLabel = nullptr;
                        HelpWidgetPixmap = nullptr;
                        setCursor(Qt::ArrowCursor);
                        CurrentPointArea = BackgroundArea::NullArea;
                        CurrentHelpStatus = HelpStatus::NotHelp;
                        return true;
                    }
                    break;
                default:
                    break;
                }
                setCursor(Qt::ArrowCursor);
                CurrentPointArea = BackgroundArea::NullArea;
                SwitchHelpStatus(HelpStatus::HelpNormal);
                return true;
            }
            return false;
        }
        return false;        
    }
    else if(obj == MenuWidgetLabel)
    {
        if(event->type() == QEvent::MouseMove)
        {
            QMouseEvent *m_QMouseEvent = static_cast<QMouseEvent*>(event);            
            switch (CurrentPointArea) 
            {
            case BackgroundArea::NullArea:
                if(InArea(BackgroundArea::MenuOKArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    SwitchMenuStatusFromHighlight(true);
                    setCursor(Qt::PointingHandCursor);
                }
                else if(InArea(BackgroundArea::MenuMusicArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    setCursor(Qt::PointingHandCursor);
                else if(InArea(BackgroundArea::MenuEffectArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    setCursor(Qt::PointingHandCursor);
                else
                {
                    SwitchMenuStatusFromHighlight(false);
                    setCursor(Qt::ArrowCursor);
                }
                break;
            case BackgroundArea::OtherArea:
                SwitchMenuStatusFromHighlight(false);
                break;
            case BackgroundArea::MenuOKArea:
                if(InArea(BackgroundArea::MenuOKArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    SwitchMenuStatusFromHighlight(true); 
                    setCursor(Qt::PointingHandCursor);
                }
                else
                {
                    SwitchMenuStatusFromHighlight(false);       
                    setCursor(Qt::ArrowCursor);
                }
            case BackgroundArea::MenuMusicArea:
                if(InArea(BackgroundArea::MenuMusicArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    setCursor(Qt::PointingHandCursor);
                else
                    setCursor(Qt::ArrowCursor);
                break;
            case BackgroundArea::MenuEffectArea:
                if(InArea(BackgroundArea::MenuEffectArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    setCursor(Qt::PointingHandCursor);
                else
                    setCursor(Qt::ArrowCursor);
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
                if(InArea(BackgroundArea::MenuOKArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    CurrentPointArea = BackgroundArea::MenuOKArea;
                else if(InArea(BackgroundArea::MenuMusicArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    CurrentPointArea = BackgroundArea::MenuMusicArea;
                else if(InArea(BackgroundArea::MenuEffectArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    CurrentPointArea = BackgroundArea::MenuEffectArea;
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
                case BackgroundArea::MenuOKArea:
                    if(InArea(BackgroundArea::MenuOKArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    {
                        delete MenuWidgetLabel;
                        delete MenuWidgetPixmap;
                        MenuWidgetLabel = nullptr;
                        MenuWidgetPixmap = nullptr;
                        setCursor(Qt::ArrowCursor);
                        CurrentPointArea = BackgroundArea::NullArea;
                        CurrentMenuStatus = MenuStatus::NotMenu;
                        return true;
                    }
                    break;
                case BackgroundArea::MenuMusicArea:
                    if(InArea(BackgroundArea::MenuMusicArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    {
                        GlobalManager::MusicOn = !(GlobalManager::MusicOn);
                        SwitchMenuStatusFromHighlight(false);
                        CurrentPointArea = BackgroundArea::NullArea;    
                        setCursor(Qt::PointingHandCursor);
                        return true;
                    }
                    break;
                case BackgroundArea::MenuEffectArea:
                    if(InArea(BackgroundArea::MenuEffectArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                    {
                        GlobalManager::EffectOn = !(GlobalManager::EffectOn);
                        SwitchMenuStatusFromHighlight(false);
                        CurrentPointArea = BackgroundArea::NullArea;
                        setCursor(Qt::PointingHandCursor);
                        return true;
                    }
                default:
                    break;
                }
                setCursor(Qt::ArrowCursor);
                CurrentPointArea = BackgroundArea::NullArea;
                SwitchMenuStatusFromHighlight(false);
                return true;
            }
            return false;
        }
        else if(event->type() == QEvent::MouseButtonDblClick)
        {
            QMouseEvent *m_QMouseEvent = static_cast<QMouseEvent*>(event);
            if(m_QMouseEvent->button() == Qt::MouseButton::LeftButton)
            {
                if(InArea(BackgroundArea::MenuMusicArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    GlobalManager::MusicOn = !(GlobalManager::MusicOn);
                    SwitchMenuStatusFromHighlight(false);
                    CurrentPointArea = BackgroundArea::NullArea;   
                    setCursor(Qt::PointingHandCursor);
                }
                else if(InArea(BackgroundArea::MenuEffectArea, m_QMouseEvent->x(), m_QMouseEvent->y()))
                {
                    GlobalManager::EffectOn = !(GlobalManager::EffectOn);
                    SwitchMenuStatusFromHighlight(false);
                    CurrentPointArea = BackgroundArea::NullArea;
                    setCursor(Qt::PointingHandCursor);
                } 
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
    case Background::Advence:
        CurrentBackground->load(":/surface/res/images/surface/SurfaceAdvence.png");
        break;
    case Background::Mini:
        CurrentBackground->load(":/surface/res/images/surface/SurfaceMini.png");
        break;
    case Background::IQ:
        CurrentBackground->load(":/surface/res/images/surface/SurfaceIQ.png");
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
    delete ExitMainWidgetPixmap;
    
    ExitMainWidgetPixmap = new QPixmap;
    switch (CurrentExitStatus) {
    case ExitStatus::ExitNormal:
        ExitMainWidgetPixmap->load(":/surface/res/images/surface/ExitMainWidgetNormal.png");
        break;
    case ExitStatus::ExitOK:
        ExitMainWidgetPixmap->load(":/surface/res/images/surface/ExitMainWidgetOK.png");
        break;
    case ExitStatus::ExitCancel:
        ExitMainWidgetPixmap->load(":/surface/res/images/surface/ExitMainWidgetCancel.png");
        break;
    default:
        break;
    }
    *ExitMainWidgetPixmap = ExitMainWidgetPixmap->scaled(ForScale(GlobalManager::StanradWindowWidth),
                                             ForScale(GlobalManager::StanradWindowWHeight),
                                             Qt::KeepAspectRatio);
    ExitMainWidgetLabel->setPixmap(*ExitMainWidgetPixmap);
}

void WelcomeWidget::SwitchHelpStatus(HelpStatus temp)
{
    if(CurrentHelpStatus == temp)
        return;
    CurrentHelpStatus = temp;
    delete HelpWidgetPixmap;
    
    HelpWidgetPixmap = new QPixmap;
    switch (CurrentHelpStatus) {
    case HelpStatus::HelpNormal:
        HelpWidgetPixmap->load(":/surface/res/images/surface/HelpWidgetNormal.png");
        break;
    case HelpStatus::HelpHighlight:
        HelpWidgetPixmap->load(":/surface/res/images/surface/HelpWidgetHighlight.png");
        break;
    default:
        break;
    }
    *HelpWidgetPixmap = HelpWidgetPixmap->scaled(ForScale(GlobalManager::StanradWindowWidth),
                                                 ForScale(GlobalManager::StanradWindowWHeight),
                                                 Qt::KeepAspectRatio);
    HelpWidgetLabel->setPixmap(*HelpWidgetPixmap);
}

void WelcomeWidget::SwitchMenuStatus(MenuStatus temp)
{
    if(CurrentMenuStatus == temp)
        return;
    CurrentMenuStatus = temp;
    delete MenuWidgetPixmap;
    
    MenuWidgetPixmap = new QPixmap;
    switch (CurrentMenuStatus) {
    case MenuStatus::MenuNNHighlight:
        MenuWidgetPixmap->load(":/surface/res/images/surface/MenuNNHighlight.png");
        break;
    case MenuStatus::MenuNNNormal:
        MenuWidgetPixmap->load(":/surface/res/images/surface/MenuNNNormal.png");
        break;
    case MenuStatus::MenuNYHighlight:
        MenuWidgetPixmap->load(":/surface/res/images/surface/MenuNYHighlight.png");
        break;
    case MenuStatus::MenuNYNormal:
        MenuWidgetPixmap->load(":/surface/res/images/surface/MenuNYNormal.png");
        break;
    case MenuStatus::MenuYNHighlight:
        MenuWidgetPixmap->load(":/surface/res/images/surface/MenuYNHighlight.png");
        break;
    case MenuStatus::MenuYNNormal:
        MenuWidgetPixmap->load(":/surface/res/images/surface/MenuYNNormal.png");
        break;
    case MenuStatus::MenuYYHighlight:
        MenuWidgetPixmap->load(":/surface/res/images/surface/MenuYYHighlight.png");
        break;
    case MenuStatus::MenuYYNormal:
        MenuWidgetPixmap->load(":/surface/res/images/surface/MenuYYNormal.png");
        break;
    default:
        break;
    }
    *MenuWidgetPixmap = MenuWidgetPixmap->scaled(ForScale(GlobalManager::StanradWindowWidth),
                                             ForScale(GlobalManager::StanradWindowWHeight),
                                             Qt::KeepAspectRatio);
    MenuWidgetLabel->setPixmap(*MenuWidgetPixmap);
}

void WelcomeWidget::SwitchMenuStatusFromHighlight(bool temp)
{
    if(temp)
    {
        if(GlobalManager::MusicOn)
        {
            if(GlobalManager::EffectOn)
                SwitchMenuStatus(MenuStatus::MenuYYHighlight);
            else
                SwitchMenuStatus(MenuStatus::MenuYNHighlight);
        }
        else
        {
            if(GlobalManager::EffectOn)
                SwitchMenuStatus(MenuStatus::MenuNYHighlight);
            else
                SwitchMenuStatus(MenuStatus::MenuNNHighlight);
        }
    }
    else
    {
        if(GlobalManager::MusicOn)
        {
            if(GlobalManager::EffectOn)
                SwitchMenuStatus(MenuStatus::MenuYYNormal);
            else
                SwitchMenuStatus(MenuStatus::MenuYNNormal);
        }
        else
        {
            if(GlobalManager::EffectOn)
                SwitchMenuStatus(MenuStatus::MenuNYNormal);
            else
                SwitchMenuStatus(MenuStatus::MenuNNNormal);
        }
    }
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
    case BackgroundArea::AdvenceArea:
        if(_x >= ForScale(481) && _x <= ForScale(787) && _y >= AdvenceLabelTop(_x) && _y <= AdvenceLabelButton(_x))
            return true;
        else
            return false;
        break;
    case BackgroundArea::MiniArea:
        if(_x >= ForScale(478) && _x <= ForScale(776)
                && _y >= ForScale((201 + ((248 - 201) * 1.0 * (_x / GlobalManager::DesktopScale - 478)) / (776 - 478)))
                && _y <= ForScale((267 + ((323 - 267) * 1.0 * (_x / GlobalManager::DesktopScale - 478)) / (776 - 478))))
            return true;
        else
            return false;        
        break;
    case BackgroundArea::IQArea:
        if(_x >= ForScale(482) && _x <= ForScale(750)
                && _y >= ForScale((308 + ((356 - 308) * 1.0 * (_x / GlobalManager::DesktopScale - 482)) / (750 - 482)))
                && _y <= ForScale((365 + ((426 - 365) * 1.0 * (_x / GlobalManager::DesktopScale - 482)) / (750 - 482))))
            return true;
        else
            return false;    
        break;
    case BackgroundArea::HelpMainArea:
        return ComparePosition(_x, _y, 365, 540, 521, 560);        
        break;
    case BackgroundArea::MenuMusicArea:
        return ComparePosition(_x, _y, 491, 526, 214, 249);
        break;
    case BackgroundArea::MenuEffectArea:
        return ComparePosition(_x, _y, 491, 526, 277, 312);
        break;
    case BackgroundArea::MenuOKArea:
        return ComparePosition(_x, _y, 295, 609, 453, 530);
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

int WelcomeWidget::AdvenceLabelTop(int x)
{
    if(x >= ForScale(481) && x <= ForScale(539))
        return ForScale(105);
    else if(x > ForScale(539) && x <= ForScale(574))
        return ForScale((105 + ((80 - 105) * 1.0 * (x / GlobalManager::DesktopScale - 539)) / (574 - 539)));
    else if(x > ForScale(574) && x <= ForScale(687))
        return ForScale(80);
    else if(x > ForScale(687) && x <= ForScale(717))
        return ForScale((80 + ((119 - 80) * 1.0 * (x / GlobalManager::DesktopScale - 687)) / (717 - 687)));
    else if(x > ForScale(717) && x <= ForScale(787))
        return ForScale((119 + ((129 - 119) * 1.0 * (x / GlobalManager::DesktopScale - 717)) / (787 - 717)));
    else
        return 0;
}

int WelcomeWidget::AdvenceLabelButton(int x)
{
    return ForScale((171 + ((218 - 171) * 1.0 * (x / GlobalManager::DesktopScale - 481)) / (787 - 481)));
}
