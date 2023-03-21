#include <string>
#include <SDL.h>

#ifndef FFT_MUSIC_VISUALISER_AUDIOPLAYER_H
#define FFT_MUSIC_VISUALISER_AUDIOPLAYER_H

class AudioPlayer {
public:
    AudioPlayer() {}

    void play_audio(const std::string & filename);
};

#endif
