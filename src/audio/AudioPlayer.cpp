#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2_mixer/SDL_mixer.h>

#include "AudioPlayer.h"

using namespace std;

void AudioPlayer::play_audio(const char * & filename) {
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
}

void AudioPlayer::initialize() {
    // Initialize SDL2 and SDL2 mixer
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Mix_OpenAudio error: %s\n", Mix_GetError());
        exit(1);
    }
}

