#ifndef FFT_MUSIC_VISUALISER_AUDIOPLAYER_H
#define FFT_MUSIC_VISUALISER_AUDIOPLAYER_H

#include <string>
#include <SDL.h>
#include <wx/wx.h>

class AudioPlayer {
public:
    void play_audio(const std::string & filename);
};

#endif
