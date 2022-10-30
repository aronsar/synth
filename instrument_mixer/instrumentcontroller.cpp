#include "instrumentcontroller.h"
#include "ui_instrumentcontroller.h"

InstrumentController::InstrumentController(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::InstrumentController)
    , ip(new InstrumentPlayer)
{
    ui->setupUi(this);

    // setup frequency slider
    ui->freq_horizontal_slider->setMinimum(MIN_FREQUENCY);
    ui->freq_horizontal_slider->setMaximum(MAX_FREQUENCY);
    ui->freq_horizontal_slider->setSliderPosition(DEFAULT_FREQUENCY);
    ui->freq_min_label->setText(QString::number(MIN_FREQUENCY));
    ui->freq_max_label->setText(QString::number(MAX_FREQUENCY));
    connect(ui->freq_horizontal_slider, SIGNAL(valueChanged(int)), this, SLOT(freq_horizontal_slider_value_changed(int)));

    // set up frequency line edit
    ui->freq_line_edit->setText(QString::number(DEFAULT_FREQUENCY));
    QValidator *freq_validator = new QIntValidator(MIN_FREQUENCY, MAX_FREQUENCY, this);
    ui->freq_line_edit->setValidator(freq_validator);
    connect(ui->freq_line_edit, SIGNAL(textEdited(QString)), this, SLOT(freq_line_edit_text_edited(QString)));
    connect(ui->freq_line_edit, SIGNAL(editingFinished()), this, SLOT(freq_line_edit_editing_finished()));

    // set up volume dial
    ui->volume_dial->setMinimum(MIN_VOLUME);
    ui->volume_dial->setMaximum(MAX_VOLUME);
    ui->volume_dial->setValue(DEFAULT_VOLUME);
    connect(ui->volume_dial, SIGNAL(valueChanged(int)), this, SLOT(volume_dial_value_changed(int)));

    // set up bpm line edit
    QValidator *bpm_validator = new QIntValidator(MIN_BPM, MAX_BPM, this);
    ui->bpm_line_edit->setValidator(bpm_validator);
    ui->bpm_line_edit->setText(QString::number(DEFAULT_BPM));
    connect(ui->bpm_line_edit, SIGNAL(textEdited(QString)), this, SLOT(bpm_line_edit_text_edited(QString)));
    connect(ui->bpm_line_edit, SIGNAL(editingFinished()), this, SLOT(bpm_line_edit_editing_finished()));

    // set up instrument selector combo box
    ui->instrument_combo_box->addItem("BeeThree");
    connect(ui->instrument_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(instrument_combo_box_current_index_changed(int)));

    // set up play button
    connect(ui->play_button, SIGNAL(clicked()), this, SLOT(play_button_clicked()));

    // set up instrument player
    float float_volume = (float)(DEFAULT_VOLUME - MIN_VOLUME) / (float)(MAX_VOLUME - MIN_VOLUME);
    ip->set_volume(float_volume);
    ip->set_frequency(DEFAULT_FREQUENCY);
    ip->set_bpm(DEFAULT_BPM);
}

void InstrumentController::instrument_combo_box_current_index_changed(int new_index)
{
    // select new instrument from instruments list
}

void InstrumentController::volume_dial_value_changed(int new_val)
{
    float float_volume = (float)(new_val - MIN_VOLUME) / (float)(MAX_VOLUME - MIN_VOLUME);
    ip->set_volume(float_volume);
}

void InstrumentController::freq_horizontal_slider_value_changed(int new_val)
{
    ui->freq_line_edit->setText(QString::number(new_val));
    ip->set_frequency(new_val);
}

void InstrumentController::freq_line_edit_text_edited(QString new_text)
{
    freq_line_edit_string = new_text;
}

void InstrumentController::freq_line_edit_editing_finished()
{
    int new_frequency = freq_line_edit_string.toInt();
    ui->freq_horizontal_slider->setSliderPosition(new_frequency);
    ip->set_frequency(new_frequency);
}

void InstrumentController::bpm_line_edit_text_edited(QString new_text)
{
    bpm_line_edit_string = new_text;
}

void InstrumentController::bpm_line_edit_editing_finished()
{
    int new_bpm = bpm_line_edit_string.toInt();
    ip->set_bpm(new_bpm);
}

void InstrumentController::play_button_clicked()
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


InstrumentController::~InstrumentController()
{
    delete ui;
    delete ip;
}
