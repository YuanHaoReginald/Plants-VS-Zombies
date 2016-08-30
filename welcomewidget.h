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
    
    enum class Background { Default, Exit, Help, Option };
    enum class BackgroundArea { NullArea, OtherArea, ExitArea, HelpArea, OptionArea };
    enum class WelcomeStatus { Normal, Exit};
    
    bool InArea(BackgroundArea, int, int);
    
protected:
    bool eventFilter(QObject *obj, QEvent *event); 
    
public slots:
	void SwitchBackground(Background);
    
private:
    BackgroundArea CurrentPointArea;
    WelcomeStatus CurrentWelcomeStatus;
    
    QLabel *BackgroundLabel;
    QPixmap *CurrentBackground;
    Background BackgroundStatus;
    
    QLabel *ExitMainWidgetLabel;
    QPixmap ExitMainWidget;
    QLabel *OKButtonLabel, *CancelButtonLabel;
    QPixmap OKButtonNormal, CancelButtonNormal, OKButtonHighlight, CancelButtonHighlight; 
};

#endif // WELCOMEWIDGET_H
