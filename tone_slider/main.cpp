#include "toneslider.h"
#include "mainwindow.h"
#include "instrumentslider.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //ToneSlider w;
    InstrumentSlider w;
    w.show();
    return a.exec();
}
