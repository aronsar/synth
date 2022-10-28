#ifndef INSTRUMENTSLIDER_H
#define INSTRUMENTSLIDER_H

#include <QWidget>
#include "instrumentplayer.h"

namespace Ui {
class InstrumentSlider;
}

class InstrumentSlider : public QWidget
{
    Q_OBJECT

    int MIN_FREQUENCY = 100;
    int MAX_FREQUENCY = 1500;
    int DEFAULT_FREQUENCY = 440;

public:
    explicit InstrumentSlider(QWidget *parent = nullptr);
    ~InstrumentSlider();

private slots:
    void instrument_combo_box_current_index_changed(int new_index);
    void freq_horizontal_slider_value_changed(int new_val);
    void freq_line_edit_text_edited(QString new_text);
    void freq_line_edit_editing_finished();
    void play_button_clicked();

private:
    Ui::InstrumentSlider *ui;
    InstrumentPlayer *ip;
    QString freq_line_edit_string = "";
    bool currently_playing = false;
};

#endif // INSTRUMENTSLIDER_H
