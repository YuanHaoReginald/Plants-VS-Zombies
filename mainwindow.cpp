#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globalmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CurrentStatusWidget = nullptr;
    setFixedWidth(GlobalManager::StanradWindowWidth * GlobalManager::DesktopScale);
    setFixedHeight(GlobalManager::StanradWindowWHeight * GlobalManager::DesktopScale);
    //switchState(MainWindow::WelcomeSurface); 
}

MainWindow::~MainWindow()
{
    delete ui;
}
