#include "spectrogram.h"
#include "ui_spectrogram.h"


Spectrogram::Spectrogram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Spectrogram)
{
    ui->setupUi(this);

    //fft_buffer = new MatrixXd(100,100);
}

Spectrogram::~Spectrogram()
{
    delete ui;
}
