#include <iostream>
#include <vector>
#include <wx/wx.h>
#include <wx/display.h>
#include <algorithm>
#include "../config.h"
#include <random>
#include "Visualiser.h"
#include "visualisers/Equalizer.h"
#include "visualisers/Circular.h"

#ifndef FFT_MUSIC_VISUALISER_WINDOW_H
#define FFT_MUSIC_VISUALISER_WINDOW_H

class Window : public wxFrame {
public:
    Window() : wxFrame(NULL, wxID_ANY, global::APP_NAME, wxDefaultPosition, wxDefaultSize) {
        create_and_start_gui_timer(10);
        create_and_start_frq_timer(10);

        equalizer_visualiser = new Equalizer();
        circular_visualiser = new Circular();
        visualiser = equalizer_visualiser;

        init_menu_bar();
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

    wxMenuBar * menu_bar;

    Equalizer * equalizer_visualiser;
    Circular * circular_visualiser;
    Visualiser * visualiser;

    void OnPaint(wxPaintEvent & event) {
        wxPaintDC graphics(this);
        visualiser->render_visualiser(graphics);
    }

    void OnGuiTimer(wxTimerEvent & event) {
        Refresh();
    }

    void OnFrqTimer(wxTimerEvent & event) {
        visualiser->update_visualiser();
    }

    void OnSize(wxSizeEvent & event) {
        wxSize size = event.GetSize();
        global::WIDTH = size.GetWidth();
        global::HEIGHT = size.GetHeight();
    }

    void OnClose(wxCloseEvent & event) {
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

    void init_menu_bar() {
        menu_bar = new wxMenuBar();

        wxMenu * file_menu = new wxMenu();
        file_menu->Append(wxID_ANY, "&Quit\tCtrl+Q");
        Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::OnQuit, this, file_menu->GetMenuItems()[0]->GetId());
        menu_bar->Append(file_menu, "&File");

        wxMenu * visualiser_menu = new wxMenu();
        visualiser_menu->Append(wxID_ANY, "Equalizer\tCtrl+E");
        visualiser_menu->Append(wxID_ANY, "Circular\tCtrl+C");
        Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::OnEqualizerSelect, this, visualiser_menu->GetMenuItems()[0]->GetId());
        Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::OnCircularSelect, this, visualiser_menu->GetMenuItems()[1]->GetId());
        menu_bar->Append(visualiser_menu, "&Visualiser");

        SetMenuBar(menu_bar);
    }

    void OnQuit(wxCommandEvent & event) {
        std::exit(0);
    }

    void OnEqualizerSelect(wxCommandEvent & event) {
        visualiser = equalizer_visualiser;
    }

    void OnCircularSelect(wxCommandEvent & event) {
        visualiser = circular_visualiser;
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
};

#endif
