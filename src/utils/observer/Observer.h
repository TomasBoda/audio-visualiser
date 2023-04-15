#ifndef FFT_MUSIC_VISUALISER_OBSERVER_H
#define FFT_MUSIC_VISUALISER_OBSERVER_H

#include <string>
#include <memory>
#include "../../audio/AudioPlayer.h"

/*
 * Observer
 * This class is used for communication between the GUI and Audio threads
 */
class Observer {
public:
    Observer(std::unique_ptr<AudioPlayer> audio_player): audio_player(std::move(audio_player)) {}

    void play(const std::string & filename);
    void resume();
    void pause();
private:
    std::unique_ptr<AudioPlayer> audio_player;
};

#endif
