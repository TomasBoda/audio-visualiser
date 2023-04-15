#ifndef FFT_MUSIC_VISUALISER_AUDIOPLAYER_H
#define FFT_MUSIC_VISUALISER_AUDIOPLAYER_H

#include <SDL.h>
#include <wx/wx.h>
#include <fftw3.h>
#include <thread>
#include <string>
#include <utility>
#include <algorithm>
#include <cmath>
#include <vector>
#include "../utils/dialog/Dialog.h"
#include "../utils/audio/Audio.h"
#include "../config/config.h"

/*
 * Audio playback handler
 * THis class represents a handler used for loading and playing audio wave files
 */
class AudioPlayer {
public:
    AudioPlayer();

    /*
     * Load audio wave file by path
     * This method load an audio wave file and stores its data into AudioData struct
     * @param filename full path to the audio wave file to be loaded
     */
    void load_audio(const std::string & filename);
    /*
     * Play the preloaded audio wave file
     * This method plays the preloaded audio wave file in a new thread
     */
    void play_audio();
    /*
     * Resume audio playback
     * This method resumes the audio playback when it's paused
     */
    void resume_audio();
    /*
     * Pause audio playback
     * This method pauses the audio playback when it's resumed
     */
    void pause_audio();

    /*
     * Load decibel levels of the audio file
     * This method calculates the decibel levels of audio file for each second and stores them
     */
    void load_volume_levels();
private:
    audio_ptr audio;
    std::thread audio_thread;

    /*
     * Audio callback
     * This method is called repeatedly when an audio file is playing and processes its current data
     * @param user_data audio data @see AudioData
     * @param stream audio stream data
     * @param length size of the current audio chunk
     */
    static void audio_callback(void * user_data, Uint8 * stream, int length);

    /*
     * Audio playback
     * This method is called when a new audio thread is started and plays the audio
     */
    void audio_playback();
    /*
     * Initialize audio
     * This method initializes the SDL library for audio processing
     */
    void initialize();
};

#endif
