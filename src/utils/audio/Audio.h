#include <utility>
#include "fftw3.h"
#include "SDL.h"

#ifndef FFT_MUSIC_VISUALISER_AUDIOUTIL_H
#define FFT_MUSIC_VISUALISER_AUDIOUTIL_H

struct AudioData {
    Uint8 * position;
    Uint32 length;
    Uint32 sample_rate;
    Uint32 channels;
    Uint32 samples;
    SDL_AudioFormat format;
};

void copy_to_stream_and_advance(Uint8 * & stream, AudioData * & audio, int length);

void free_fftw_data(fftw_complex * & fft_input, fftw_complex * & fft_output, fftw_plan & fft_plan);

void copy_stream_to_fft_input(fftw_complex * & fft_input, AudioData * & audio);

std::pair<size_t, size_t> frequency_range_to_bin_indexes(int low_frequency, int high_frequency, AudioData * & audio);

double magnitude_to_db(double magnitude);

#endif
