#include "fft.h"
#include "spectrogram.h"


FFT::FFT(int _input_buffer_length, int _output_buffer_length) :
        input_buffer_length(_input_buffer_length),
        output_buffer_length(_output_buffer_length),
        input_buffer(new StkFloat[input_buffer_length]),
        complex_buffer(new CArray(input_buffer_length)),
        output_buffer(new StkFloat[output_buffer_length])
{
}


// Cooley–Tukey FFT (in-place)
void fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;

    // divide
    CArray even = x[std::slice(0, N/2, 2)];
    CArray  odd = x[std::slice(1, N/2, 2)];

    // conquer
    fft(even);
    fft(odd);

    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}


void FFT::calculate()
{
    for (int i = 0; i < input_buffer_length; i++)
    {
        double hanning_coeff = 0.5 * (1 - cos(2 * PI * i / input_buffer_length));
        //std::cout<<hanning_coeff<<std::endl;
        (*complex_buffer)[i] = Complex(hanning_coeff * input_buffer[i], 0);
    }

    fft(*complex_buffer);

    for (int i = 0; i < output_buffer_length; i++)
    {
        output_buffer[i] = std::abs((*complex_buffer)[i]);
    }
}
