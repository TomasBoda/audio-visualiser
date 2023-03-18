#include <string>
#include <SDL.h>
#include "../window/Window.h"

#ifndef FFT_MUSIC_VISUALISER_AUDIOPLAYER_H
#define FFT_MUSIC_VISUALISER_AUDIOPLAYER_H

class AudioPlayer {
public:
    AudioPlayer() {}

    void play_audio(const char * & filename);
};

#endif
