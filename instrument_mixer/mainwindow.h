#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Voicer.h"
#include "RtAudio.h"
#include "circularbuffer.h"

using namespace stk;

struct TickData
{
    Voicer *voicer;
    CircularBuffer<StkFloat> *audio_buffer;
};

inline int tick( void *_outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData )
{
    TickData *data = (TickData *) userData;
    StkFloat *outputBuffer = (StkFloat *) _outputBuffer;

    for ( unsigned int i=0; i<nBufferFrames; i++ ) {
        StkFloat sample = data->voicer->tick();
        data->audio_buffer->put(sample);
        *outputBuffer++ = sample;
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
    TickData tick_data;
    RtAudio dac;
};
#endif // MAINWINDOW_H
