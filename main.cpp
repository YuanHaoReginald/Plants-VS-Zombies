#include "mainwindow.h"
#include "globalmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    initGlobalManager();
    MainWindow w;
    w.show();
    
    return a.exec();
}
