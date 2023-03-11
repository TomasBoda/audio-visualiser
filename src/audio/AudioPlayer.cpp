#include <iostream>
#include <thread>
#include <random>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2_mixer/SDL_mixer.h>
#include "../config.h"
#include "AudioPlayer.h"

using namespace std;

Uint8 * audio_position;
Uint32 audio_length;

void audio_callback(void * user_data, Uint8 * stream, int length) {
    if (audio_length == 0) {
        return;
    }

    int buffer_size = length > audio_length ? audio_length : length;
    SDL_memcpy (stream, audio_position, buffer_size);

    audio_position += buffer_size;
    audio_length -= buffer_size;

    // generate random int and update global data
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10);

    int shared_data = dist(gen);
    std::lock_guard<std::mutex> lock(global::MUTEX);
    global::SHARED_DATA = shared_data;
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

        wav_spec.callback = audio_callback;
        wav_spec.userdata = NULL;

        audio_position = wav_buffer;
        audio_length = wav_length;

        if (SDL_OpenAudio(&wav_spec, NULL) < 0) {
            cerr << "Cannot open audio..." << endl;
            exit(1);
        }

        SDL_PauseAudio(0);
        while (audio_length > 0) {
            SDL_Delay(100);
        }

        SDL_CloseAudio();
        SDL_FreeWAV(wav_buffer);
    });

    audio_thread.detach();
}

