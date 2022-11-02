#include "instrumentcontroller.h"
#include "Bowed.h"
#include "Brass.h"
#include "Clarinet.h"
#include "Flute.h"
#include "Mandolin.h"
#include "Plucked.h"
#include "Recorder.h"
#include "Resonate.h"
#include "Saxofony.h"
#include "Sitar.h"
#include "Whistle.h"
#include "ui_instrumentcontroller.h"
#include "Voicer.h"

std::map<int, QString> InstrumentNameMap {
    {BOWED, "Bowed"},
    {BRASS, "Brass"},
    {CLARINET, "Clarinet"},
    {FLUTE, "Flute"},
    {MANDOLIN, "Mandolin"},
    {PLUCKED, "Plucked"},
    {RECORDER, "Recorder"},
    {RESONATE, "Resonate"},
    {SAXOFONY, "Saxofony"},
    {SITAR, "Sitar"},
    {WHISTLE, "Whistle"},
};

Instrmnt *create_instrument(int instrument_index)
{
    switch (instrument_index)
    {
    case BOWED:
        return new Bowed();
    case BRASS:
        return new Brass();
    case CLARINET:
        return new Clarinet();
    case FLUTE:
        return new Flute(220);
    case MANDOLIN:
        return new Mandolin(220);
    case PLUCKED:
        return new Plucked();
    case RECORDER:
        return new Recorder();
    case RESONATE:
        return new Resonate();
    case SAXOFONY:
        return new Saxofony(220);
    case SITAR:
        return new Sitar();
    case WHISTLE:
        return new Whistle();
    }
}


InstrumentController::InstrumentController(QWidget *parent) :
    QWidget(parent)
    , ui(new Ui::InstrumentController)
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
    for (int i = 0; i < NUM_INSTRUMENTS; i++)
        ui->instrument_combo_box->addItem(InstrumentNameMap[i]);
    ui->instrument_combo_box->setCurrentIndex(DEFAULT_INSTRUMENT);
    connect(ui->instrument_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(instrument_combo_box_current_index_changed(int)));

    // set up play button
    connect(ui->play_button, SIGNAL(clicked()), this, SLOT(play_button_clicked()));

    // set up instrument
    current_instrument = create_instrument(DEFAULT_INSTRUMENT);
    this->frequency = DEFAULT_FREQUENCY;
    this->bpm = DEFAULT_BPM;
    this->currently_playing = false;
    this->amplitude = convert_dial_volume_to_voicer_amplitude(DEFAULT_VOLUME);
}

InstrumentController::~InstrumentController()
{
    delete ui;
    delete current_instrument;
}

void InstrumentController::set_group(int _group)
{
    this->group = _group;
}

void InstrumentController::set_voicer(Voicer *_voicer)
{
    this->voicer = _voicer;
    this->voicer->addInstrument(this->current_instrument, this->group);
}

StkFloat InstrumentController::convert_dial_volume_to_voicer_amplitude(int dial_volume)
{
    return 128.0 * (float)(dial_volume - MIN_VOLUME) / (float)(MAX_VOLUME - MIN_VOLUME);
}

void InstrumentController::instrument_combo_box_current_index_changed(int instrument_index)
{
    voicer->removeInstrument(current_instrument);
    delete current_instrument;
    current_instrument = create_instrument(instrument_index);
    voicer->addInstrument(current_instrument);
}

void InstrumentController::volume_dial_value_changed(int new_val)
{
    this->amplitude = convert_dial_volume_to_voicer_amplitude(new_val);
}

void InstrumentController::freq_horizontal_slider_value_changed(int new_val)
{
    ui->freq_line_edit->setText(QString::number(new_val));
    this->frequency = new_val;
}

void InstrumentController::freq_line_edit_text_edited(QString new_text)
{
    freq_line_edit_string = new_text;
}

void InstrumentController::freq_line_edit_editing_finished()
{
    this->frequency = freq_line_edit_string.toInt();
    ui->freq_horizontal_slider->setSliderPosition(this->frequency);
}

void InstrumentController::bpm_line_edit_text_edited(QString new_text)
{
    bpm_line_edit_string = new_text;
}

void InstrumentController::bpm_line_edit_editing_finished()
{
    this->bpm = bpm_line_edit_string.toInt();
}

void InstrumentController::play_button_clicked()
{
    if (!this->currently_playing)
    {
        this->currently_playing = true;
        ui->play_button->setText("PAUSE");
        this->note_repeater_thread = std::thread( [this] { __note_repeater(); } );

    }
    else
    {
        this->currently_playing = false;
        ui->play_button->setText("PLAY");
        this->note_repeater_thread.join();
    }
}

void InstrumentController::__note_repeater()
{
    while(this->currently_playing)
    {
        long note_tag = voicer->noteOn(this->frequency, this->amplitude, this->group);
        int duration_ms = 1000 * 60 / this->bpm - 100; // integer division
        Stk::sleep(duration_ms);
        voicer->noteOff(note_tag, this->amplitude);
        Stk::sleep(100); // time between notes
    }
}


