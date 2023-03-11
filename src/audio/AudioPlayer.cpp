#include <iostream>
#include <thread>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2_mixer/SDL_mixer.h>

#include "AudioPlayer.h"

using namespace std;

void AudioPlayer::play_audio(const char * & filename) {
    thread audio_thread( [filename]() {
        Mix_Chunk * audio_file = Mix_LoadWAV(filename);

        if (audio_file == nullptr) {
            printf("Mix_LoadWAV error: %s\n", Mix_GetError());
            exit(1);
        }

        Mix_PlayChannel(-1, audio_file, 0);
        cout << "Playing " << filename << "..." << endl;

        while (Mix_Playing(-1) != 0) {
            SDL_Delay(100);
        }

        Mix_FreeChunk(audio_file);
        Mix_CloseAudio();
        SDL_Quit();

    });

    audio_thread.detach();
}

void AudioPlayer::initialize() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        cout << "Error initialising SDL2 library...";
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "Error initialising SDL2 library...";
        exit(1);
    }
}

