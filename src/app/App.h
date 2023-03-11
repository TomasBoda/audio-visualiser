#include <wx/wx.h>
#include <iostream>
#include "../window/Window.h"
#include "../audio/AudioPlayer.h"

#ifndef FFT_MUSIC_VISUALISER_APP_H
#define FFT_MUSIC_VISUALISER_APP_H

class App : public wxApp {
public:
    virtual bool OnInit();
private:
    Window * window;
};

bool App::OnInit() {
    window = new Window("Music Visualiser", wxPoint(50, 50), wxSize(800, 500));

    AudioPlayer audio_player;
    const char * filename = "../never-gonna-give-u-up.wav";
    audio_player.play_audio(filename);

    return true;
}

#endif
