#include <utility>
#include <fftw3.h>
#include <SDL.h>

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

void copy_to_stream_and_advance(Uint8 * & stream, AudioData * & audio, int length) {
    SDL_memcpy(stream, audio->position, length);
    audio->position += length;
    audio->length -= length;
}

void free_fftw_data(fftw_complex * & fft_input, fftw_complex * & fft_output, fftw_plan & fft_plan) {
    fftw_destroy_plan(fft_plan);
    fftw_free(fft_input);
    fftw_free(fft_output);
}

void copy_stream_to_fft_input(fftw_complex * & fft_input, AudioData * & audio) {
    Uint32 window_size = audio->samples;

    for (int i = 0; i < window_size; i++) {
        if (audio->format == AUDIO_F32) {
            float * audio_data = (float*) audio->position;
            fft_input[i][0] = audio_data[i * audio->channels];
            fft_input[i][1] = 0.0;
        } else if (audio->format == AUDIO_S16SYS) {
            Sint16 * audio_data = (Sint16*) audio->position;
            fft_input[i][0] = (double) audio_data[i * audio->channels] / 32768.0;
            fft_input[i][1] = 0.0;
        }
    }
}

std::pair<size_t, size_t> frequency_range_to_bin_indexes(int low_frequency, int high_frequency, AudioData * & audio) {
    int window_size = audio->samples;
    int num_bins = window_size / 2 + 1;
    Uint32 sample_rate = audio->sample_rate;

    std::pair<size_t, size_t> indexes;

    for (int i = 0; i < num_bins - 1; i++) {
        double hz1 = i * sample_rate / window_size;
        double hz2 = (i + 1) * sample_rate / window_size;

        if (hz1 < low_frequency && hz2 >= low_frequency) {
            indexes.first = i + 1;
        }

        if (hz1 <= high_frequency && hz2 > high_frequency) {
            indexes.second = i;
            break;
        }
    }

    return indexes;
}

double magnitude_to_db(double magnitude) {
    return 20 * log10(magnitude);
}

#endif
