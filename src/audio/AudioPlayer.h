#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2_mixer/SDL_mixer.h>
#include "../window/Window.h"

#ifndef FFT_MUSIC_VISUALISER_AUDIOPLAYER_H
#define FFT_MUSIC_VISUALISER_AUDIOPLAYER_H

class AudioPlayer {
public:
    AudioPlayer() { initialize(); }

    void play_audio(const char * & filename);
private:
    void initialize();
};

#endif
