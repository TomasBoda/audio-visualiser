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

    /*
     * Play new audio file
     * This method loads a new audio file and starts playing it
     * @param filename path to the audio file to be played
     */
    void play(const std::string & filename);
    /*
     * Resume audio playback
     * This method resumes the audio playback if it has been paused
     */
    void resume();
    /*
     * Pause audio playback
     * This method pauses the audio playback if it has been resumed
     */
    void pause();
private:
    std::unique_ptr<AudioPlayer> audio_player;
};

#endif
