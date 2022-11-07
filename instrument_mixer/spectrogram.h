#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H

#include <QWidget>
#include <vector>

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

    std::vector<std::vector<int>> frequency_graph;
};

#endif // SPECTROGRAM_H
