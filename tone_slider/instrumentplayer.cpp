#include "instrumentplayer.h"

using namespace stk;

// This tick() function handles sample computation only.  It will be
// called automatically when the system needs a new buffer of audio
// samples.
int tick( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData )
{
  TickData *data = (TickData *) userData;
  StkFloat *samples = (StkFloat *) outputBuffer;

  for ( unsigned int i=0; i<nBufferFrames; i++ ) {
    *samples++ = data->instrument->tick();
    if ( ++data->counter % 2000 == 0 ) {
      data->scaler += 0.025;
      data->instrument->setFrequency( data->frequency * data->scaler );
    }
  }

  if ( data->counter > 80000 )
    data->done = true;

  return 0;
}


InstrumentPlayer::InstrumentPlayer()
{
    Stk::setSampleRate(44100);
    Stk::setRawwavePath( "../stk/rawwaves/" );

    TickData data;
    RtAudio dac;

    // Figure out how many bytes in an StkFloat and setup the RtAudio stream.
    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = 1;
    RtAudioFormat format = ( sizeof(StkFloat) == 8 ) ? RTAUDIO_FLOAT64 : RTAUDIO_FLOAT32;
    unsigned int bufferFrames = RT_BUFFER_SIZE;

    try
    {
        dac.openStream( &parameters, NULL, format, (unsigned int)Stk::sampleRate(), &bufferFrames, &tick, (void *)&data );
    }
    catch ( RtAudioError& error )
    {
        error.printMessage();
    }

    data.instrument = new BeeThree();
    data.frequency = 200;
}

void InstrumentPlayer::set_voicer(Voicer *_voicer)
{
    if (_voicer)
        this->voicer = _voicer;
    else
        this->voicer = new Voicer();
}

void InstrumentPlayer::start_audio(void)
{

}

void InstrumentPlayer::stop_audio(void)
{

}

void InstrumentPlayer::set_frequency(int frequency)
{

}

void InstrumentPlayer::set_bpm(int bpm)
{

}


InstrumentPlayer::~InstrumentPlayer()
{
    delete data.instrument;
}
