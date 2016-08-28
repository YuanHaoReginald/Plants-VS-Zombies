#ifndef ABSTRACTWINDOW_H
#define ABSTRACTWINDOW_H

#include <QWidget>
#include "globalmanager.h"

class AbstractWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractWidget(QWidget *parent = 0);
    
signals:
    void StatusChanged(GameStatus);
    
public slots:
};

#endif // ABSTRACTWINDOW_H
