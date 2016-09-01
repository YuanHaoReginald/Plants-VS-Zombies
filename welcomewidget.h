#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include "abstractwidget.h"
#include <QLabel>
#include <QPixmap>

class WelcomeWidget : public AbstractWidget
{
public:
    WelcomeWidget(QWidget *parent);
    ~WelcomeWidget();
    
private:
    enum class Background { NoBackGround, Default, Exit, Help, Option, Advence, Mini, IQ };
    enum class BackgroundArea { NullArea, OtherArea, ExitArea, HelpArea, OptionArea, 
                                ExitOKArea, ExitCancelArea, AdvenceArea, MiniArea, IQArea };
    enum class ExitStatus { NotExit, ExitNormal, ExitOK, ExitCancel };
    
    bool InArea(BackgroundArea, int, int);
    bool ComparePosition(int _x, int _y, int xMin, int xMax, int yMin, int yMax);
    
protected:
    bool eventFilter(QObject *obj, QEvent *event); 
    
public slots:
	void SwitchBackground(Background);
    void SwitchExitStatus(ExitStatus);
    
private:
    BackgroundArea CurrentPointArea;
    
    QLabel *BackgroundLabel;
    QPixmap *CurrentBackground;
    Background BackgroundStatus;
    
    QLabel *ExitMainWidgetLabel;
    QPixmap *ExitMainWidget;
    ExitStatus CurrentExitStatus;
    
    int AdvenceLabelTop(int x);
    int AdvenceLabelButton(int x);
    
};

#endif // WELCOMEWIDGET_H
