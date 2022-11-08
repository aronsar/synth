#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Voicer.h"
#include "RtAudio.h"
#include "circularbuffer.hpp"

using namespace stk;

struct TickData
{
    Voicer *voicer;
    CircularBuffer<StkFloat> *fft_input_buffer;
};

int tick( void *_outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData )
{
    TickData *data = (TickData *) userData;
    StkFloat *outputBuffer = (StkFloat *) _outputBuffer;

    for ( unsigned int i=0; i<nBufferFrames; i++ ) {
        StkFloat sample = data->voicer->tick();
        data->fft_input_buffer->put(sample);
        *outputBuffer++ = sample;
        //if (!(sample == 0))
        //    std::cout << sample << std::endl;
    }
    return 0;
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TickData *data;
    RtAudio dac;
};
#endif // MAINWINDOW_H
