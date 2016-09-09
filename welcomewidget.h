#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include "abstractwidget.h"
#include <QLabel>
#include <QMediaPlayer>
#include <QPixmap>

class WelcomeWidget : public AbstractWidget
{
    Q_OBJECT
    
public:
    WelcomeWidget(QWidget *parent);
    ~WelcomeWidget();
    
private:
    enum class Background { NoBackGround, Default, Exit, Help, Option, Advence, Mini, IQ };
    enum class BackgroundArea { NullArea, OtherArea, ExitArea, HelpArea, OptionArea, HelpMainArea,
                                ExitOKArea, ExitCancelArea, AdvenceArea, MiniArea, IQArea,
                                MenuMusicArea, MenuEffectArea, MenuOKArea };
    enum class ExitStatus { NotExit, ExitNormal, ExitOK, ExitCancel };
    enum class HelpStatus { NotHelp, HelpNormal, HelpHighlight };
    enum class MenuStatus { NotMenu, MenuNNNormal, MenuNYNormal, MenuYNNormal, MenuYYNormal,
                            MenuNNHighlight, MenuNYHighlight, MenuYNHighlight, MenuYYHighlight };
    
    bool InArea(BackgroundArea, int, int);
    bool ComparePosition(int _x, int _y, int xMin, int xMax, int yMin, int yMax);
    
protected:
    bool eventFilter(QObject *obj, QEvent *event); 
    
public slots:
	void SwitchBackground(Background);
    void SwitchExitStatus(ExitStatus);
    void SwitchHelpStatus(HelpStatus);
    void SwitchMenuStatus(MenuStatus); 
    void SwitchMenuStatusFromHighlight(bool);
    
private:
    BackgroundArea CurrentPointArea;
    
    QLabel *BackgroundLabel;
    QPixmap *CurrentBackground;
    Background BackgroundStatus;
    
    QLabel *ExitMainWidgetLabel;
    QPixmap *ExitMainWidgetPixmap;
    ExitStatus CurrentExitStatus;
    
    QLabel *HelpWidgetLabel;
    QPixmap *HelpWidgetPixmap;
    HelpStatus CurrentHelpStatus;
    
    QLabel *MenuWidgetLabel;
    QPixmap *MenuWidgetPixmap;
    MenuStatus CurrentMenuStatus;
    
    QMediaPlayer* WelcomeMedia;
    
    int AdvenceLabelTop(int x);
    int AdvenceLabelButton(int x);
    
};

#endif // WELCOMEWIDGET_H
