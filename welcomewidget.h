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
    enum class BackgroundArea { ExitArea, HelpArea, OptionArea };
    
    bool InArea(BackgroundArea, int, int);
    
protected:
    bool eventFilter(QObject *obj, QEvent *event); 
    
public slots:
	void SwitchBackground(Background);
    
private:
    QLabel *BackgroundLabel;
    //QLabel *ExitMainWidgetLabel;
    QPixmap *CurrentBackground;
   // QPixmap *ExitMainWidget;
    Background BackgroundStatus;
};

#endif // WELCOMEWIDGET_H
