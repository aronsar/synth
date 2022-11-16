#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H

#include <QWidget>
#include <vector>
#include <Eigen/Dense>
#include "Stk.h"
#include "circularbuffer.h"
#include "fft.h"

using Eigen::MatrixXd;
using namespace stk;

class Spectrogram : public QWidget
{
    Q_OBJECT

public:
    explicit Spectrogram(QWidget *parent = nullptr);
    ~Spectrogram();
    inline void set_audio_buffer(CircularBuffer<StkFloat> *buffer) {audio_buffer_ = buffer;}

public slots:
    void nextAnimationFrame();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    FFT fft = FFT(100,100);
    CircularBuffer<StkFloat> *audio_buffer_;
    QImage frequency_graph = QImage(100, 100, QImage::Format_RGB32);

    void shift_frequency_graph_columns_one_left();
    void copy_fft_output_buffer_to_frequency_graph();
    QColor convert_fft_output_to_color(StkFloat fft_output_float);

};

#endif // SPECTROGRAM_H
