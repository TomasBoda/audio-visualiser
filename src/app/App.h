#include <wx/wx.h>
#include <iostream>
#include "../gui/Window.h"
#include "../audio/AudioPlayer.h"

#ifndef FFT_MUSIC_VISUALISER_APP_H
#define FFT_MUSIC_VISUALISER_APP_H

class App : public wxApp {
public:
    virtual bool OnInit();
private:
    Window * window;
    AudioPlayer * audio_player;
};

bool App::OnInit() {
    window = new Window();
    audio_player = new AudioPlayer();

    audio_player->play_audio(global::FILENAME);

    return true;
}

#endif
