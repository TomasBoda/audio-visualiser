#include <wx/wx.h>
#include "../window/Window.h"
#include "../audio/AudioPlayer.h"
#include "../config.h"

#ifndef FFT_MUSIC_VISUALISER_APP_H
#define FFT_MUSIC_VISUALISER_APP_H

class App : public wxApp {
public:
    virtual bool OnInit();
private:
    Window * window;
};

bool App::OnInit() {
    window = new Window("Music Visualiser", wxPoint(50, 50), wxSize(constants::WIDTH, constants::HEIGHT));

    AudioPlayer audio_player;
    audio_player.play_audio(constants::FILENAME);

    return true;
}

#endif
