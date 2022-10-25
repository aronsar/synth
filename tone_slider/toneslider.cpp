#include "toneslider.h"
#include "./ui_toneslider.h"
#include "sineloop.h"

ToneSlider::ToneSlider(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ToneSlider)
    , sl(new SineLoop)
{
    ui->setupUi(this);
    ui->horizontalSlider->setMaximum(1000);

    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(update_textlabel_with_slider_val(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(update_audio_frequency_with_slider_val(int)));
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(start_button_clicked()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stop_button_clicked()));
}

void ToneSlider::update_textlabel_with_slider_val(int val)
{
    ui->label->setText(QString::number(val));
}

void ToneSlider::update_audio_frequency_with_slider_val(int val)
{
    sl->set_frequency(val);
}

void ToneSlider::start_button_clicked(void)
{
    sl->start_audio();
}

void ToneSlider::stop_button_clicked(void)
{
    sl->stop_audio();
}

ToneSlider::~ToneSlider()
{
    delete ui;
    delete sl;
}

