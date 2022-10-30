#ifndef INSTRUMENTCONTROLLER_H
#define INSTRUMENTCONTROLLER_H

#include <QWidget>
#include "instrumentplayer.h"

namespace Ui {
class InstrumentController;
}

class InstrumentController : public QWidget
{
    Q_OBJECT

    int MIN_FREQUENCY = 100;
    int MAX_FREQUENCY = 1500;
    int DEFAULT_FREQUENCY = 440;
    int MIN_VOLUME = 0;
    int MAX_VOLUME = 11;
    int DEFAULT_VOLUME = 5;
    int MIN_BPM = 10;
    int MAX_BPM = 420;
    int DEFAULT_BPM = 60;

public:
    explicit InstrumentController(QWidget *parent = nullptr);
    ~InstrumentController();

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
    InstrumentPlayer *ip;
    QString freq_line_edit_string = "";
    QString bpm_line_edit_string = "";
    bool currently_playing = false;
};

#endif // INSTRUMENTCONTROLLER_H
