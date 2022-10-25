#include "toneslider.h"
#include "./ui_toneslider.h"
#include "sineloop.h"
#include <string>
#include <QIntValidator>

ToneSlider::ToneSlider(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ToneSlider)
    , sl(new SineLoop)
{
    ui->setupUi(this);
    ui->horizontalSlider->setMinimum(MIN_FREQUENCY);
    ui->horizontalSlider->setMaximum(MAX_FREQUENCY);
    ui->minFreqLabel->setText(QString::number(MIN_FREQUENCY));
    ui->maxFreqLabel->setText(QString::number(MAX_FREQUENCY));

    ui->horizontalSlider->setSliderPosition(DEFAULT_FREQUENCY);
    ui->lineEdit->setText(QString::number(DEFAULT_FREQUENCY));
    sl->set_frequency(DEFAULT_FREQUENCY);

    QValidator *validator = new QIntValidator(MIN_FREQUENCY, MAX_FREQUENCY, this);
    ui->lineEdit->setValidator(validator);



    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)),   this, SLOT(horizontal_slider_value_changed(int)));
    connect(ui->lineEdit,         SIGNAL(textEdited(QString)), this, SLOT(line_edit_text_edited(QString)));
    connect(ui->lineEdit,         SIGNAL(editingFinished()),   this, SLOT(line_edit_editing_finished()));
    connect(ui->startButton,      SIGNAL(clicked()),           this, SLOT(start_button_clicked()));
    connect(ui->stopButton,       SIGNAL(clicked()),           this, SLOT(stop_button_clicked()));
}

void ToneSlider::horizontal_slider_value_changed(int val)
{
    ui->lineEdit->setText(QString::number(val));
    sl->set_frequency(val);
}

void ToneSlider::line_edit_text_edited(QString str)
{
    line_edit_string = str;
}

void ToneSlider::line_edit_editing_finished(void)
{
    int new_frequency = line_edit_string.toInt();
    ui->horizontalSlider->setSliderPosition(new_frequency);
    sl->set_frequency(new_frequency);
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

