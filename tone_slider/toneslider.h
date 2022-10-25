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

    int MIN_FREQUENCY = 100;
    int MAX_FREQUENCY = 1500;
    int DEFAULT_FREQUENCY = 440;

public slots:
    void horizontal_slider_value_changed(int val);
    void line_edit_text_edited(QString str);
    void line_edit_editing_finished(void);
    void start_button_clicked(void);
    void stop_button_clicked(void);

public:
    ToneSlider(QWidget *parent = nullptr);
    ~ToneSlider();

private:
    Ui::ToneSlider *ui;
    SineLoop *sl;
    QString line_edit_string = "";
};
#endif // TONESLIDER_H
