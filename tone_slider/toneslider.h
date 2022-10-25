#ifndef TONESLIDER_H
#define TONESLIDER_H

#include <QWidget>
#include "sineloop.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ToneSlider; }
QT_END_NAMESPACE

class ToneSlider : public QWidget
{
    Q_OBJECT

public slots:
    void update_textlabel_with_slider_val(int val);
    void update_audio_frequency_with_slider_val(int val);
    void start_button_clicked(void);
    void stop_button_clicked(void);

public:
    ToneSlider(QWidget *parent = nullptr);
    ~ToneSlider();

private:
    Ui::ToneSlider *ui;
    SineLoop *sl;
    SineLoop *sl_2;
};
#endif // TONESLIDER_H
