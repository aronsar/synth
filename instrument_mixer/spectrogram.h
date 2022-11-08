#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H

#include <QWidget>
#include <vector>
#include <Eigen/Dense>

using Eigen::MatrixXd;

namespace Ui {
class Spectrogram;
}

class Spectrogram : public QWidget
{
    Q_OBJECT

public:
    explicit Spectrogram(QWidget *parent = nullptr);
    ~Spectrogram();

private:
    Ui::Spectrogram *ui;

    MatrixXd *fft_input_buffer;
    int buffer_idx = 0;
};

#endif // SPECTROGRAM_H
