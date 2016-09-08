#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globalmanager.h"
#include "welcomewidget.h"
#include "advencewidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CurrentStatusWidget = nullptr;
    setFixedWidth(ForScale(GlobalManager::StanradWindowWidth));
    setFixedHeight(ForScale(GlobalManager::StanradWindowWHeight));
    //setFixedWidth(2560);
    //setFixedHeight(1440);
    SwitchStatus(GameStatus::Welcome); 
}

MainWindow::~MainWindow()
{
    delete ui;
    delete CurrentStatusWidget;
}

void MainWindow::SwitchStatus(GameStatus TargetStatus)
{
	if (CurrentStatusWidget == nullptr || CurrentStatus != TargetStatus)
	{
		CurrentStatus = TargetStatus;
		delete CurrentStatusWidget;
		switch (CurrentStatus)
		{
        case GameStatus::Welcome:
			CurrentStatusWidget = new WelcomeWidget(this);
            GlobalManager::CurrentWidget = CurrentStatusWidget;
			break;
        case GameStatus::Advence:
            CurrentStatusWidget = new AdvenceWidget(this);
            GlobalManager::CurrentWidget = CurrentStatusWidget;            
            break;
		default:
			break;
		}
		connect(CurrentStatusWidget, SIGNAL(StatusChanged(GameStatus)), this, SLOT(SwitchStatus(GameStatus)));
		CurrentStatusWidget->show();
	}
}
