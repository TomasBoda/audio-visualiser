#ifndef FFT_MUSIC_VISUALISER_WINDOW_H
#define FFT_MUSIC_VISUALISER_WINDOW_H

#include <iostream>
#include <vector>
#include "wx/wx.h"
#include "wx/display.h"
#include <algorithm>
#include "../../config/config.h"
#include <random>
#include "../../utils/visualiser/Visualiser.h"
#include "../visualisers/equalizer/Equalizer.h"
#include "../visualisers/circular/Circular.h"
#include "../../utils/frame/Frame.h"
#include "../../utils/observer/Observer.h"
#include "../../utils/dialog/Dialog.h"

class Window : public Frame {
public:
    Window();

    /*
     * Render components in the window
     * This method renders custom components in the window
     * @param graphics graphics object @see wxDC
     */
    void render(Graphics graphics) override;
    /*
     * Update components in the window
     * This method is used for updating custom components in the window
     */
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

    void on_choose(Event event);
    void on_quit(Event event);
    void on_resume(Event event);
    void on_pause(Event event);
    void on_equalizer_select(Event event);
    void on_circular_select(Event event);

    void init_menu_bar();
};

#endif