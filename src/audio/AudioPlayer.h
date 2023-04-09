#ifndef FFT_MUSIC_VISUALISER_AUDIOPLAYER_H
#define FFT_MUSIC_VISUALISER_AUDIOPLAYER_H

#include <string>
#include <SDL.h>
#include <wx/wx.h>
#include <thread>
#include <utility>
#include <fftw3.h>
#include <algorithm>
#include <cmath>
#include "../utils/dialog/Dialog.h"
#include "../utils/audio/Audio.h"
#include "../config/config.h"

class AudioPlayer {
public:
    AudioPlayer();

    void load_audio(const std::string & filename);
    void play_audio();
    void resume_audio();
    void pause_audio();
private:
    AudioData audio;
    std::thread audio_thread;

    static void audio_callback(void * user_data, Uint8 * stream, int length);

    void audio_playback();
    void initialize();
};

#endif
