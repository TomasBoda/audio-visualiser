#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <complex>
#include "../config.h"
#include "AudioPlayer.h"
#include "../utils/FFT.h"

using namespace std;

struct AudioData {
    Uint8 * position;
    Uint32 length;
    Uint32 sample_rate;
};

void audio_callback(void * user_data, Uint8 * stream, int length) {
    AudioData * audio = (AudioData *) user_data;

    Uint32 buffer_size = length > audio->length ? audio->length : length;
    SDL_memcpy(stream, audio->position, buffer_size);

    vector<complex<double>> x(buffer_size / 2);
    for (size_t i = 0; i < buffer_size / 2; i++) {
        x[i].real(stream[i * 2]);
        x[i].imag(stream[i * 2 + 1]);
    }

    const size_t N = x.size() / 2;
    const double chunk_size = N / global::NUM_CHUNKS;

    for (size_t i = 0; i < global::NUM_CHUNKS; i++) {
        double chunk_sum = 0;

        for (size_t j = 0; j < chunk_size; j++) {
            int index = (i * chunk_size) + j;

            double frequency = index * audio->sample_rate / (double) N;
            double magnitude = std::abs(x[index]);
            chunk_sum += magnitude;
        }

        global::SPECTRUM[i] = chunk_sum / chunk_size;
    }

    audio->position += buffer_size;
    audio->length -= buffer_size;
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

