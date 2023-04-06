#include <iostream>
#include <vector>
#include <wx/wx.h>
#include <wx/display.h>
#include <algorithm>
#include "../config/config.h"
#include <random>
#include "../utils/Visualiser.h"
#include "visualisers/Equalizer.h"
#include "visualisers/Circular.h"
#include "../utils/Frame.h"

#ifndef FFT_MUSIC_VISUALISER_WINDOW_H
#define FFT_MUSIC_VISUALISER_WINDOW_H

class Window : public Frame {
public:
    Window() {
        equalizer_visualiser = new Equalizer();
        circular_visualiser = new Circular();
        visualiser = equalizer_visualiser;

        init_menu_bar();
        init_keyboard_shortcuts();
    };

    void render(wxDC & graphics) override {
        visualiser->render_visualiser(graphics);
    }

    void update() override {
        visualiser->update_visualiser();
    }
private:
    wxMenuBar * menu_bar;

    Equalizer * equalizer_visualiser;
    Circular * circular_visualiser;
    Visualiser * visualiser;

    void on_quit(wxCommandEvent & event) {
        std::exit(0);
    }

    void init_menu_bar() {
        menu_bar = new wxMenuBar();

        wxMenu * file_menu = new wxMenu();
        file_menu->Append(wxID_ANY, "&Quit\tCtrl+Q");
        Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::on_quit, this, file_menu->GetMenuItems()[0]->GetId());
        menu_bar->Append(file_menu, "&File");

        wxMenu * visualiser_menu = new wxMenu();
        visualiser_menu->Append(wxID_ANY, "Equalizer\tCtrl+E");
        visualiser_menu->Append(wxID_ANY, "Circular\tCtrl+C");
        Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::OnEqualizerSelect, this, visualiser_menu->GetMenuItems()[0]->GetId());
        Bind(wxEVT_COMMAND_MENU_SELECTED, &Window::OnCircularSelect, this, visualiser_menu->GetMenuItems()[1]->GetId());
        menu_bar->Append(visualiser_menu, "&Visualiser");

        SetMenuBar(menu_bar);
    }

    void init_keyboard_shortcuts() {
        wxAcceleratorEntry shortcuts[3];

        shortcuts[0].Set(wxACCEL_CTRL, (int) 'Q', wxID_ANY);
        shortcuts[1].Set(wxACCEL_CTRL, (int) 'E', wxID_ANY);
        shortcuts[2].Set(wxACCEL_CTRL, (int) 'C', wxID_ANY);

        wxAcceleratorTable shortcut_table(3, shortcuts);
        SetAcceleratorTable(shortcut_table);
    }

    void OnEqualizerSelect(wxCommandEvent & event) {
        visualiser = equalizer_visualiser;
    }

    void OnCircularSelect(wxCommandEvent & event) {
        visualiser = circular_visualiser;
    }
};

#endif
