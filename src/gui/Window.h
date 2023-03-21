#include <iostream>
#include <vector>
#include <wx/wx.h>
#include <algorithm>
#include "../config.h"
#include <random>

#ifndef FFT_MUSIC_VISUALISER_WINDOW_H
#define FFT_MUSIC_VISUALISER_WINDOW_H

class Window : public wxFrame {
public:
    Window() : wxFrame(NULL, wxID_ANY, global::APP_NAME, wxDefaultPosition, wxDefaultSize) {
        gui_timer = new wxTimer(this, wxID_ANY);
        frq_timer = new wxTimer(this, wxID_ANY);

        Bind(wxEVT_PAINT, &Window::OnPaint, this);
        Bind(wxEVT_TIMER, &Window::OnGuiTimer, this, gui_timer->GetId());
        Bind(wxEVT_TIMER, &Window::OnFrqTimer, this, frq_timer->GetId());

        gui_timer->Start(10);
        frq_timer->Start(10);

        SetBackgroundColour(wxColour(* wxBLACK));
        SetSize(wxSize(global::WIDTH, global::HEIGHT));
        Center();
        ShowFullScreen(false);
        Show(true);
    };

    ~Window() {
        gui_timer->Stop();
        frq_timer->Stop();
        delete gui_timer;
        delete frq_timer;
    }
private:
    wxTimer * gui_timer;
    wxTimer * frq_timer;
    double frequency_spectrum[180];

    wxPen pen_inner_lines { wxColour(40, 40, 40), 3 };
    wxPen pen_outer_lines { wxColour(255, 255, 255), 5 };
    wxPen pen_inner_circle { wxColour(255, 255, 255), 5 };
    wxBrush brush_inner_circle { wxColour(0, 0, 0) };

    void OnGuiTimer(wxTimerEvent& event) {
        apply_gravity_to_frequency_spectrum();
        Refresh();
    }

    void OnFrqTimer(wxTimerEvent& event) {
        copy_and_normalize_frequency_spectrum();
    }

    void OnPaint(wxPaintEvent& event) {
        draw_circle_visualisation(event);
    }

    void OnClose(wxCloseEvent& event) {
        gui_timer->Stop();
        frq_timer->Stop();
        Destroy();
    }

    void draw_spectrum_visualisation(wxPaintEvent & event);
    void draw_circle_visualisation(wxPaintEvent & event);

    void copy_and_normalize_frequency_spectrum();
    void apply_gravity_to_frequency_spectrum();
};

#endif
