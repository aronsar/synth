#include "spectrogram.h"
#include "ui_spectrogram.h"


Spectrogram::Spectrogram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Spectrogram)
{
    ui->setupUi(this);


}

Spectrogram::~Spectrogram()
{
    delete ui;
}
