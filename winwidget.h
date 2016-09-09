#ifndef WINWIDGET_H
#define WINWIDGET_H

#include "abstractwidget.h"
#include <QLabel>
#include <QPixmap>

class WinWidget : public AbstractWidget
{
    Q_OBJECT
    
public:
    WinWidget(QWidget* parent);
    ~WinWidget();
    
private:
    QLabel* WinLabel;
    QPixmap* WinPixmap;
    
protected:
    void mousePressEvent();
};

#endif // WINWIDGET_H
