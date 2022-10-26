#include "instrumentplayer.h"
#include "instrumentslider.h"
#include "ui_instrumentslider.h"

InstrumentSlider::InstrumentSlider(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::InstrumentSlider)
    , ip(new InstrumentPlayer)
{
    ui->setupUi(this);

    ui->freq_horizontal_slider->setMinimum(MIN_FREQUENCY);
    ui->freq_horizontal_slider->setMaximum(MAX_FREQUENCY);
    ui->freq_min_label->setText(QString::number(MIN_FREQUENCY));
    ui->freq_max_label->setText(QString::number(MAX_FREQUENCY));

    ui->freq_horizontal_slider->setSliderPosition(DEFAULT_FREQUENCY);
    ui->freq_line_edit->setText(QString::number(DEFAULT_FREQUENCY));
    //sl->set_frequency(DEFAULT_FREQUENCY);

    QValidator *validator = new QIntValidator(MIN_FREQUENCY, MAX_FREQUENCY, this);
    ui->freq_line_edit->setValidator(validator);

    ui->instrument_combo_box->addItem("one");
    ui->instrument_combo_box->addItem("two");
    ui->instrument_combo_box->addItem("three");

    //ip->set_voicer(nullptr);

    connect(ui->instrument_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(instrument_combo_box_current_index_changed(int)));
}

void InstrumentSlider::instrument_combo_box_current_index_changed(int new_index)
{
    // select new instrument from instruments list
}


InstrumentSlider::~InstrumentSlider()
{
    delete ui;
    delete ip;
}
