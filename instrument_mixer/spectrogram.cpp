#include "spectrogram.h"
#include "qpainter.h"

int AUDIO_BUFFER_LENGTH = 2000;
int NUM_FREQ_BINS = AUDIO_BUFFER_LENGTH / 2;
int FREQ_GRAPH_HISTORY_LENGTH = 500;

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
    for (int y = 0; y < NUM_FREQ_BINS; y++)
    {
        for (int x = 0; x < FREQ_GRAPH_HISTORY_LENGTH-1; x++)
        {
            QColor target_color = frequency_graph.pixelColor(x+1, y);
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
    //std::cout << fft_output_float << std::endl;
    int b = std::max(0, std::min(255, int(fft_output_float * 25.5)));
    QColor color = QColor(b, b, b);
    if (not color.isValid())
        exit(0);
    return color;
}

void Spectrogram::copy_fft_output_buffer_to_frequency_graph()
{
    for (int y = 0; y < NUM_FREQ_BINS; y++)
    {
        double bin_size = Stk::sampleRate() / AUDIO_BUFFER_LENGTH;
        double max_freq = Stk::sampleRate() / 2.0;
        double min_freq = bin_size;
        double freq = min_freq * pow(10, (double)(y)/NUM_FREQ_BINS * log10(max_freq / min_freq));
        double w = (freq - min_freq) / bin_size;
        int w_int = int(w);
        //std::cout << w_int << std::endl;
        double w_rem = w - w_int;
        StkFloat val = (w_rem*fft.output_buffer[w_int] + (1-w_rem)*fft.output_buffer[w_int+1])/2; // modify to geometric mean instead

        QColor target_color = this->convert_fft_output_to_color(val);
        frequency_graph.setPixelColor(FREQ_GRAPH_HISTORY_LENGTH - 1, y, target_color);
    }
}

void Spectrogram::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    audio_buffer_->copy_to(fft.input_buffer, fft.input_buffer_length);
    fft.calculate();
    this->shift_frequency_graph_columns_one_left();
    this->copy_fft_output_buffer_to_frequency_graph();

    QRect target(0, 0, FREQ_GRAPH_HISTORY_LENGTH, 500);
    QRect source(0, 0, FREQ_GRAPH_HISTORY_LENGTH, NUM_FREQ_BINS);

    painter.drawImage(target, frequency_graph, source);
}
