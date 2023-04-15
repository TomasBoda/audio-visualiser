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
    Window * window;
    AudioPlayer * audio_player;
    Observer * observer;
};

#endif
