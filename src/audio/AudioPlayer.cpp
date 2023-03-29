#include <iostream>
#include <thread>
#include <cmath>
#include <SDL.h>
#include "../config.h"
#include "AudioPlayer.h"
#include <algorithm>
#include "../utils/Dialog.h"
#include <fftw3.h>
#include <utility>
#include "AudioUtil.h"

using namespace std;

void audio_callback(void * user_data, Uint8 * stream, int length) {
    AudioData * audio = (AudioData *) user_data;
    Uint32 window_size = audio->samples;

    fftw_complex * fft_input = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * window_size);
    fftw_complex * fft_output = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * window_size);
    fftw_plan fft_plan = fftw_plan_dft_1d(window_size, fft_input, fft_output, FFTW_FORWARD, FFTW_ESTIMATE);

    copy_stream_to_fft_input(fft_input, audio);
    fftw_execute(fft_plan);

    int low_frequency = 0;
    int high_frequency = 20000;

    pair<size_t, size_t> bin_range = frequency_range_to_bin_indexes(low_frequency, high_frequency, audio);
    size_t start_bin = bin_range.first;
    size_t end_bin = bin_range.second;

    int num_bins = end_bin - start_bin;

    double * db_values = new double[num_bins];
    for (int i = start_bin; i < end_bin; i++) {
        int index = i - start_bin;

        double real_part = fft_output[i][0];
        double imag_part = fft_output[i][1];

        double magnitude = sqrt(real_part * real_part + imag_part * imag_part);
        double db_value = magnitude_to_db(magnitude);

        db_values[index] = db_value;
    }

    int num_chunks = global::NUM_CHUNKS;
    int chunk_width = num_bins / num_chunks;

    double * db_chunks = new double[num_chunks];
    for (int i = 0; i < num_chunks; i++) {
        double db_sum = 0;

        for (int j = 0; j < chunk_width; j++) {
            int index = i * chunk_width + j;
            db_sum += db_values[index];
        }

        db_chunks[i] = db_sum / chunk_width;
        global::SPECTRUM[i] = db_chunks[i];
    }

    free_fftw_data(fft_input, fft_output, fft_plan);
    copy_to_stream_and_advance(stream, audio, length);
}

void AudioPlayer::play_audio(const string & filename) {
    thread audio_thread( [filename]() {
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            Dialog::showErrorMessage("Audio library could not be initialized...");
        }

        Uint32 wav_length;
        Uint8 * wav_buffer;
        SDL_AudioSpec wav_spec;

        if (SDL_LoadWAV(filename.c_str(), &wav_spec, &wav_buffer, &wav_length) == NULL) {
            Dialog::showErrorMessage("Cannot open the provided audio file...");
        }

        AudioData audio;
        audio.position = wav_buffer;
        audio.length = wav_length;
        audio.sample_rate = wav_spec.freq;
        audio.channels = wav_spec.channels;
        audio.samples = wav_spec.samples;
        audio.format = wav_spec.format;

        wav_spec.callback = audio_callback;
        wav_spec.userdata = &audio;

        if (SDL_OpenAudio(&wav_spec, NULL) < 0) {
            Dialog::showErrorMessage("Cannot open the provided audio file...");
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

