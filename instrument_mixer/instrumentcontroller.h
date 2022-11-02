#ifndef INSTRUMENTCONTROLLER_H
#define INSTRUMENTCONTROLLER_H

#include <QWidget>
#include "Instrmnt.h"
#include "Voicer.h"
#include <thread>
#include <map>

enum InstrumentIndexEnum {
    BOWED,
    BRASS,
    CLARINET,
    FLUTE,
    MANDOLIN,
    PLUCKED,
    RECORDER,
    RESONATE,
    SAXOFONY,
    SITAR,
    WHISTLE,
    NUM_INSTRUMENTS
};

extern std::map<int, QString> InstrumentNameMap;

namespace Ui {
class InstrumentController;
}

using namespace stk;

class InstrumentController : public QWidget
{
    Q_OBJECT

    const int MIN_FREQUENCY = 45;
    const int MAX_FREQUENCY = 93;
    const int DEFAULT_FREQUENCY = 57;
    const int MIN_VOLUME = 0;
    const int MAX_VOLUME = 11;
    const int DEFAULT_VOLUME = 5;
    const int MIN_BPM = 10;
    const int MAX_BPM = 420;
    const int DEFAULT_BPM = 180;
    const int DEFAULT_INSTRUMENT = PLUCKED;

public:
    explicit InstrumentController(QWidget *parent = nullptr);
    ~InstrumentController();
    void set_group(int _group);
    void set_voicer(Voicer *_voicer);

private slots:
    void instrument_combo_box_current_index_changed(int new_index);
    void volume_dial_value_changed(int new_val);
    void freq_horizontal_slider_value_changed(int new_val);
    void freq_line_edit_text_edited(QString new_text);
    void freq_line_edit_editing_finished();
    void bpm_line_edit_text_edited(QString new_text);
    void bpm_line_edit_editing_finished();
    void play_button_clicked();

private:
    Ui::InstrumentController *ui;
    QString freq_line_edit_string;
    QString bpm_line_edit_string;
    bool currently_playing;
    Voicer *voicer = nullptr;
    Instrmnt *current_instrument = nullptr;
    StkFloat amplitude;
    int frequency;
    int bpm;
    std::thread note_repeater_thread;
    int group;

    void __note_repeater();
    StkFloat convert_dial_volume_to_voicer_amplitude(int dial_volume);
};

#endif // INSTRUMENTCONTROLLER_H
