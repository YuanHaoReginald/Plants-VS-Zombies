#ifndef WINWIDGET_H
#define WINWIDGET_H

#include "abstractwidget.h"
#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>

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
    void mousePressEvent(QMouseEvent* event);
};

#endif // WINWIDGET_H
