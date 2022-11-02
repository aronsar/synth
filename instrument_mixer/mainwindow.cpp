#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Voicer.h"




int tick2( void *_outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData )
{
    Voicer *voicer = (Voicer *) userData;
    StkFloat *outputBuffer = (StkFloat *) _outputBuffer;

    for ( unsigned int i=0; i<nBufferFrames; i++ ) {
        StkFloat sample = voicer->tick();
        *outputBuffer++ = sample;
        //if (!(sample == 0))
        //    std::cout << sample << std::endl;
    }
    return 0;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , voicer(new Voicer)
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

    ui->instrument_controller_1->set_group(0);
    ui->instrument_controller_2->set_group(1);
    ui->instrument_controller_3->set_group(2);

    ui->instrument_controller_1->set_voicer(voicer);
    ui->instrument_controller_2->set_voicer(voicer);
    ui->instrument_controller_3->set_voicer(voicer);

    dac.openStream( &parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick2, (void *)voicer );
    dac.startStream();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete voicer;
    dac.closeStream();
}

