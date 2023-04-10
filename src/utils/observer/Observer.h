#ifndef FFT_MUSIC_VISUALISER_OBSERVER_H
#define FFT_MUSIC_VISUALISER_OBSERVER_H

#include <string>
#include "../../audio/AudioPlayer.h"

/*
 * Observer
 * This class is used for communication between the GUI and Audio threads
 */
class Observer {
public:
    Observer(AudioPlayer * audio_player): audio_player(audio_player) {}

    void play(const std::string & filename);
    void resume();
    void pause();
private:
    AudioPlayer * audio_player;
};

#endif
