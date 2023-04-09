#ifndef FFT_MUSIC_VISUALISER_WINDOW_H
#define FFT_MUSIC_VISUALISER_WINDOW_H

#include <iostream>
#include <vector>
#include "wx/wx.h"
#include "wx/display.h"
#include <algorithm>
#include "../../config/config.h"
#include <random>
#include "../../utils/Visualiser.h"
#include "../visualisers/equalizer/Equalizer.h"
#include "../visualisers/circular/Circular.h"
#include "../../utils/frame/Frame.h"
#include "../../utils/observer/Observer.h"
#include "../../utils/Dialog.h"

class Window : public Frame {
public:
    Window();

    void render(wxDC & graphics) override;
    void update() override;

    void set_observer(Observer * observer) {
        this->observer = observer;
    }
private:
    Equalizer * equalizer_visualiser;
    Circular * circular_visualiser;

    Visualiser * visualiser;
    Observer * observer;

    wxMenuBar * menu_bar;

    void on_quit(wxCommandEvent & event);
    void on_equalizer_select(wxCommandEvent & event);
    void on_circular_select(wxCommandEvent & event);

    void init_menu_bar();
};

#endif
