#include <wx/wx.h>
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

#endif
