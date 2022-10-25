#include "toneslider.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToneSlider w;
    w.show();
    return a.exec();
}
