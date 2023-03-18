#include <iostream>
#include <thread>
#include <cmath>
#include <SDL.h>
#include "../config.h"
#include "AudioPlayer.h"
#include "../utils/FFT.h"
#include <algorithm>

#include <fftw3.h>

using namespace std;

struct AudioData {
    Uint8 * position;
    Uint32 length;
    Uint32 sample_rate;
};

void audio_callback(void * user_data, Uint8 * stream, int len) {
    AudioData * audio = (AudioData *) user_data;

    int num_samples = len / 2;

    fftw_complex * in = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * num_samples);
    fftw_complex * out = (fftw_complex *) fftw_malloc(sizeof(fftw_complex) * num_samples);
    fftw_plan plan = fftw_plan_dft_1d(num_samples, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    for (int i = 0; i < num_samples; i++) {
        Sint16 sample = ((Sint16) audio->position[2 * i + 1] << 8) | audio->position[2 * i];
        double normalized_sample = (double) sample / 32768.0;

        in[i][0] = normalized_sample;
        in[i][1] = 0;
    }

    fftw_execute(plan);

    const int num_bins = global::NUM_CHUNKS;
    double bin_width = (double) audio->sample_rate / (double) num_samples;

    double * magnitudes = new double[num_bins];
    for (int i = 0; i < num_bins; i++) {
        double frequency = bin_width * i;
        double magnitude = sqrt(out[i][0] * out[i][0] + out[i][1] * out[i][1]);
        magnitudes[i] = magnitude;
    }

    double * db_values = new double[num_bins];
    for (int i = 0; i < num_bins; i++) {
        double db_value = 20.0 * log10(magnitudes[i] + 1e-6);
        db_values[i] = max(0.0, db_value);
        global::SPECTRUM[i] = db_values[i] * 10;
    }

    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    SDL_memcpy(stream, audio->position, len);
    audio->position += len;
    audio->length -= len;
}

void AudioPlayer::play_audio(const char * & filename) {
    thread audio_thread( [filename]() {
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            cerr << "SDL error occurred..." << endl;
            exit(1);
        }

        Uint32 wav_length;
        Uint8 * wav_buffer;
        SDL_AudioSpec wav_spec;

        if (SDL_LoadWAV(filename, &wav_spec, &wav_buffer, &wav_length) == NULL) {
            cerr << "Cannot open audio file..." << endl;
            exit(1);
        }

        AudioData audio;
        audio.position = wav_buffer;
        audio.length = wav_length;
        audio.sample_rate = wav_spec.freq;

        wav_spec.callback = audio_callback;
        wav_spec.userdata = &audio;

        if (SDL_OpenAudio(&wav_spec, NULL) < 0) {
            cerr << "Cannot open audio..." << endl;
            exit(1);
        }

        SDL_PauseAudio(0);
        while (audio.length > 0) {
            SDL_Delay(1);
        }

        SDL_CloseAudio();
        SDL_FreeWAV(wav_buffer);
    });

    audio_thread.detach();
}

