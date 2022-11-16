#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Voicer.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Stk::setSampleRate(8000);
    Stk::setRawwavePath( "../../stk/rawwaves/" );

    // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = 1;
    RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    unsigned int bufferFrames = RT_BUFFER_SIZE;

    ui->setupUi(this);

    tick_data.voicer = new Voicer();
    tick_data.audio_buffer = new CircularBuffer<StkFloat>(100);

    ui->instrument_controller_1->set_group(0);
    ui->instrument_controller_2->set_group(1);
    ui->instrument_controller_3->set_group(2);

    ui->instrument_controller_1->set_voicer(tick_data.voicer);
    ui->instrument_controller_2->set_voicer(tick_data.voicer);
    ui->instrument_controller_3->set_voicer(tick_data.voicer);

    //ui->spectrogram->set_fft_input_buffer(tick_data.fft_input_buffer);

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

