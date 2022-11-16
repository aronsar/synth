#include "spectrogram.h"
#include "qpainter.h"


Spectrogram::Spectrogram(QWidget *parent) :
    QWidget(parent)
{
    /* To repaint the graph, do the following:
     * copy the buffer over from audio_buffer to fft.input_buffer
     * fft.calculate()
     * shift over all the pixmap columns
     * copy the buffer from fft.output_buffer to the right most column
     */
    frequency_graph.fill(QColor("black"));
}

Spectrogram::~Spectrogram()
{
}

void Spectrogram::shift_frequency_graph_columns_one_left()
{
    for (int y = 0; y < 100; y++)
    {
        for (int x = 0; x < 100-1; x++)
        {
            QColor target_color = frequency_graph.pixelColor(x, y+1);
            frequency_graph.setPixelColor(x, y, target_color);
        }
    }
}

void Spectrogram::nextAnimationFrame()
{
    update();
}

QColor Spectrogram::convert_fft_output_to_color(StkFloat fft_output_float)
{
    int blue = int((fft_output_float+1)/2*255);
    return QColor(255, 255, blue);
}

void Spectrogram::copy_fft_output_buffer_to_frequency_graph()
{
    for (int y = 0; y < 100; y++)
    {
        QColor target_color = this->convert_fft_output_to_color(fft.output_buffer[y]);
        frequency_graph.setPixelColor(100, y, target_color);
    }
}

void Spectrogram::paintEvent(QPaintEvent *)
{
    QPainter painter(this);


    audio_buffer_->copy_to(fft.input_buffer, fft.input_buffer_length);
    fft.calculate();
    this->shift_frequency_graph_columns_one_left();
    this->copy_fft_output_buffer_to_frequency_graph();

    QRect target(0, 0, 100, 100);
    QRect source(0, 0, 100, 100);

    painter.drawImage(target, frequency_graph, source);
}
