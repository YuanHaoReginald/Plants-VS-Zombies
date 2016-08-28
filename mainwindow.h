#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    enum GameStatus { WelcomeSurface };

public slots:
	//void switchState(MainWindow::GameStatus);

private:
	GameStatus CurrentStatus;
	QWidget *CurrentStatusWidget;
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
