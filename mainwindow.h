#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "globalmanager.h"
#include "abstractwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
	void SwitchStatus(GameStatus);

private:
	GameStatus CurrentStatus;
	AbstractWidget *CurrentStatusWidget;
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
