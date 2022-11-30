#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Voicer.h"

#include <QTimer>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Stk::setSampleRate(44100);
    Stk::setRawwavePath( "../thirdparty/stk/rawwaves/" );

    // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = 1;
    RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    unsigned int bufferFrames = RT_BUFFER_SIZE;

    ui->setupUi(this);

    tick_data.voicer = new Voicer();
    tick_data.audio_buffer = new CircularBuffer<StkFloat>(AUDIO_BUFFER_LENGTH);

    ui->instrument_controller_1->set_group(0);
    ui->instrument_controller_2->set_group(1);
    ui->instrument_controller_3->set_group(2);

    ui->instrument_controller_1->set_voicer(tick_data.voicer);
    ui->instrument_controller_2->set_voicer(tick_data.voicer);
    ui->instrument_controller_3->set_voicer(tick_data.voicer);

    ui->spectrogram->set_audio_buffer(tick_data.audio_buffer);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, ui->spectrogram, &Spectrogram::nextAnimationFrame);
    timer->start(5);

    dac.openStream( &parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)&tick_data );
    dac.startStream();
}

MainWindow::~MainWindow()
{
    dac.closeStream();

    delete ui;
    delete tick_data.voicer;
    delete tick_data.audio_buffer;
}

