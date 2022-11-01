#include "mainwindow.h"
#include "instrumentcontroller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //InstrumentController w;
    w.show();
    return a.exec();
}
