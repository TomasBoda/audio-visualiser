#ifndef FFT_MUSIC_VISUALISER_OBSERVER_H
#define FFT_MUSIC_VISUALISER_OBSERVER_H

#include <string>
#include "../../audio/AudioPlayer.h"

class Observer {
public:
    Observer(AudioPlayer * audio_player): audio_player(audio_player) {}

    void play_audio(const std::string & filename) {
        audio_player->play_audio(filename);
    }
private:
    AudioPlayer * audio_player;
};

#endif
