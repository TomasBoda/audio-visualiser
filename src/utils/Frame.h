#ifndef FFT_MUSIC_VISUALISER_FRAME_H
#define FFT_MUSIC_VISUALISER_FRAME_H

#include <wx/wx.h>
#include <wx/display.h>
#include "../config/config.h"

class Frame : public wxFrame {
public:
    Frame() : wxFrame(NULL, wxID_ANY, "wxFrame", wxDefaultPosition, wxDefaultSize) {
        initialize_timers();
        initialize();
        initialize_window();
    }

    ~Frame() {
        render_timer->Stop();
        update_timer->Stop();
        delete render_timer;
        delete update_timer;
    }

    virtual void initialize() {};
    virtual void render(wxPaintDC & graphics) {};
    virtual void update() {};
private:
    wxTimer * render_timer;
    wxTimer * update_timer;

    const size_t render_timer_refresh_rate = 10;
    const size_t update_timer_refresh_rate = 10;

    void OnPaint(wxPaintEvent & event) {
        wxPaintDC graphics(this);
        render(graphics);
    }

    void OnSize(wxSizeEvent & event) {
        wxSize size = event.GetSize();
        global::WIDTH = size.GetWidth();
        global::HEIGHT = size.GetHeight();
    }

    void OnClose(wxCloseEvent & event) {
        render_timer->Stop();
        update_timer->Stop();
        Destroy();
    }

    void on_render_timer(wxTimerEvent & event) {
        Refresh();
    }

    void on_update_timer(wxTimerEvent & event) {
        update();
    }

    void initialize_window() {
        Bind(wxEVT_PAINT, &Frame::OnPaint, this);
        Bind(wxEVT_SIZE, &Frame::OnSize, this);

        init_default_size();

        Center();
        SetBackgroundColour(wxColour(* wxBLACK));
        Show(true);
    }

    void init_default_size() {
        wxDisplay display;
        wxRect screenRect = display.GetClientArea();
        SetSize(screenRect);

        global::WIDTH = screenRect.width;
        global::HEIGHT = screenRect.height;
    }

    void initialize_timers() {
        render_timer = new wxTimer(this, wxID_ANY);
        update_timer = new wxTimer(this, wxID_ANY);

        Bind(wxEVT_TIMER, &Frame::on_render_timer, this, render_timer->GetId());
        Bind(wxEVT_TIMER, &Frame::on_update_timer, this, update_timer->GetId());

        render_timer->Start(render_timer_refresh_rate);
        update_timer->Start(update_timer_refresh_rate);
    }
};

#endif
