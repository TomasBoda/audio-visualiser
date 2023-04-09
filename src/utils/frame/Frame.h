#ifndef FFT_MUSIC_VISUALISER_FRAME_H
#define FFT_MUSIC_VISUALISER_FRAME_H

#include "wx/wx.h"
#include "wx/display.h"
#include "wx/dcbuffer.h"
#include "../../config/config.h"

class Frame : public wxFrame {
public:
    Frame();
    ~Frame();

    virtual void initialize() {};
    virtual void render(wxDC & graphics) {};
    virtual void update() {};
private:
    wxTimer * render_timer;
    wxTimer * update_timer;

    const size_t render_timer_refresh_rate = 10;
    const size_t update_timer_refresh_rate = 10;

    void OnPaint(wxPaintEvent & event);
    void OnSize(wxSizeEvent & event);
    void OnClose(wxCloseEvent & event);

    void on_render_timer(wxTimerEvent & event);
    void on_update_timer(wxTimerEvent & event);

    void initialize_window();
    void init_default_size();
    void initialize_timers();
};

#endif
