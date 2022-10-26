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
    void instrument_combo_box_current_index_changed(int);

private:
    Ui::InstrumentSlider *ui;
    InstrumentPlayer *ip;
};

#endif // INSTRUMENTSLIDER_H
