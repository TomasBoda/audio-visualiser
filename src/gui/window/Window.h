#ifndef FFT_MUSIC_VISUALISER_WINDOW_H
#define FFT_MUSIC_VISUALISER_WINDOW_H

#include <wx/wx.h>
#include <wx/display.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <memory>
#include "../../config/config.h"
#include "../../utils/visualiser/Visualiser.h"
#include "../visualisers/equalizer/Equalizer.h"
#include "../visualisers/circular/Circular.h"
#include "../visualisers/volumes/Volumes.h"
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

    void set_observer(std::unique_ptr<Observer> & observer) {
        this->observer = std::move(observer);
    }
private:
    Equalizer * equalizer_visualiser;
    Circular * circular_visualiser;
    Volumes * volumes_visualiser;
    Visualiser * visualiser;

    std::unique_ptr<Observer> observer;

    wxMenuBar * menu_bar;

    void on_choose(Event event);

    void on_quit(Event event);
    void on_resume(Event event);
    void on_pause(Event event);

    void on_equalizer_select(Event event);
    void on_circular_select(Event event);
    void on_volumes_select(Event event);

    void init_menu_bar();
};

#endif
