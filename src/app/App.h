#ifndef FFT_MUSIC_VISUALISER_APP_H
#define FFT_MUSIC_VISUALISER_APP_H

#include <wx/wx.h>
#include <memory>
#include "../gui/window/Window.h"
#include "../audio/AudioPlayer.h"
#include "../utils/observer/Observer.h"

class App : public wxApp {
public:
    virtual bool OnInit();
private:
    std::unique_ptr<Window> window;
    std::unique_ptr<AudioPlayer> audio_player;
    std::unique_ptr<Observer> observer;
};

#endif
