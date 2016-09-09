#ifndef FAILWIDGET_H
#define FAILWIDGET_H

#include "abstractwidget.h"
#include <QLabel>
#include <QPixmap>

class FailWidget : public AbstractWidget
{
    Q_OBJECT
    
public:
    FailWidget(QWidget* parent);
    ~FailWidget();
    
private:
    QLabel* FailLabel;
    QPixmap* FailPixmap;
    
protected:
    void mousePressEvent();
};

#endif // FAILWIDGET_H
