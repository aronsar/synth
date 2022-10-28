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
    ip->set_frequency(DEFAULT_FREQUENCY);

    QValidator *validator = new QIntValidator(MIN_FREQUENCY, MAX_FREQUENCY, this);
    ui->freq_line_edit->setValidator(validator);

    ui->instrument_combo_box->addItem("BeeThree");

    //ip->set_voicer(nullptr);

    connect(ui->instrument_combo_box,   SIGNAL(currentIndexChanged(int)), this, SLOT(instrument_combo_box_current_index_changed(int)));
    connect(ui->freq_horizontal_slider, SIGNAL(valueChanged(int)),        this, SLOT(freq_horizontal_slider_value_changed(int)));
    connect(ui->freq_line_edit,         SIGNAL(textEdited(QString)),      this, SLOT(freq_line_edit_text_edited(QString)));
    connect(ui->freq_line_edit,         SIGNAL(editingFinished()),        this, SLOT(freq_line_edit_editing_finished()));
    connect(ui->play_button,            SIGNAL(clicked()),                this, SLOT(play_button_clicked()));
}

void InstrumentSlider::instrument_combo_box_current_index_changed(int new_index)
{
    // select new instrument from instruments list
}

void InstrumentSlider::freq_horizontal_slider_value_changed(int new_val)
{
    ui->freq_line_edit->setText(QString::number(new_val));
    ip->set_frequency(new_val);
}

void InstrumentSlider::freq_line_edit_text_edited(QString new_text)
{
    freq_line_edit_string = new_text;
}

void InstrumentSlider::freq_line_edit_editing_finished()
{
    int new_frequency = freq_line_edit_string.toInt();
    ui->freq_horizontal_slider->setSliderPosition(new_frequency);
    ip->set_frequency(new_frequency);
}

void InstrumentSlider::play_button_clicked()
{
    if (this->currently_playing)
    {
        ip->stop_audio();
        this->currently_playing = false;
        ui->play_button->setText("PLAY");
    }
    else
    {
        ip->start_audio();
        this->currently_playing = true;
        ui->play_button->setText("PAUSE");
    }
}


InstrumentSlider::~InstrumentSlider()
{
    delete ui;
    delete ip;
}
