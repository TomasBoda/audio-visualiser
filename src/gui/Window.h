#include <iostream>
#include <vector>
#include <wx/wx.h>
#include <wx/display.h>
#include <algorithm>
#include "../config.h"
#include <random>

#ifndef FFT_MUSIC_VISUALISER_WINDOW_H
#define FFT_MUSIC_VISUALISER_WINDOW_H

class Window : public wxFrame {
public:
    Window() : wxFrame(NULL, wxID_ANY, global::APP_NAME, wxDefaultPosition, wxDefaultSize), frequency_spectrum(new double[global::NUM_CHUNKS]) {
        create_and_start_gui_timer(10);
        create_and_start_frq_timer(10);

        init_default_spectrum_values();
        init_default_window();
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
    double * frequency_spectrum;

    wxPen pen_inner_lines { wxColour(40, 40, 40), 3 };
    wxPen pen_outer_lines { wxColour(255, 255, 255), 5 };
    wxPen pen_inner_circle { wxColour(255, 255, 255), 5 };
    wxBrush brush_inner_circle { wxColour(0, 0, 0) };

    void OnPaint(wxPaintEvent& event) {
        //draw_circle_visualisation(event);
        draw_spectrum_visualisation(event);
    }

    void OnGuiTimer(wxTimerEvent & event) {
        apply_gravity_to_frequency_spectrum();
        Refresh();
    }

    void OnFrqTimer(wxTimerEvent & event) {
        copy_and_normalize_frequency_spectrum();
    }

    void OnSize(wxSizeEvent& event) {
        wxSize size = event.GetSize();
        global::WIDTH = size.GetWidth();
        global::HEIGHT = size.GetHeight();
    }

    void OnClose(wxCloseEvent& event) {
        gui_timer->Stop();
        frq_timer->Stop();
        Destroy();
    }

    void create_and_start_gui_timer(int refresh_rate) {
        gui_timer = new wxTimer(this, wxID_ANY);
        Bind(wxEVT_TIMER, &Window::OnGuiTimer, this, gui_timer->GetId());
        gui_timer->Start(refresh_rate);
    }

    void create_and_start_frq_timer(int refresh_rate) {
        frq_timer = new wxTimer(this, wxID_ANY);
        Bind(wxEVT_TIMER, &Window::OnFrqTimer, this, frq_timer->GetId());
        frq_timer->Start(refresh_rate);
    }

    void init_default_window() {
        init_default_display_size();

        Bind(wxEVT_PAINT, &Window::OnPaint, this);
        Bind(wxEVT_SIZE, &Window::OnSize, this);

        init_default_display_size();

        SetBackgroundColour(wxColour(* wxBLACK));
        Center();
        Show(true);
    }

    void init_default_display_size() {
        wxDisplay display;
        wxRect screenRect = display.GetClientArea();
        global::WIDTH = screenRect.width;
        global::HEIGHT = screenRect.height;
        SetSize(screenRect);
    }

    void init_default_spectrum_values() {
        for (int i = 0; i < global::NUM_CHUNKS; i++) {
            frequency_spectrum[i] = -global::HEIGHT / 2;
        }
    }

    void draw_spectrum_visualisation(wxPaintEvent & event);
    void draw_circle_visualisation(wxPaintEvent & event);

    void copy_and_normalize_frequency_spectrum();
    void apply_gravity_to_frequency_spectrum();
};

#endif
