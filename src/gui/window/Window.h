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
    ~Window() noexcept;

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

    /*
     * Set observer
     * This method sets the observer
     * @param observer observer to be set
     */
    void set_observer(std::unique_ptr<Observer> observer);
private:
    std::shared_ptr<Equalizer> equalizer_visualiser;
    std::shared_ptr<Circular> circular_visualiser;
    std::shared_ptr<Volumes> volumes_visualiser;
    std::shared_ptr<Visualiser> visualiser;

    std::unique_ptr<Observer> observer;

    wxMenuBar * menu_bar;

    /*
     * Choose new audio file
     * This method opens the file chooser dialog and the user can select the next audio file to be played
     */
    void on_choose(Event event);

    /*
     * Quit application
     * This method quits the application
     */
    void on_quit(Event event);
    /*
     * Resume audio playback
     * This method resumes the audio playback if it has been paused
     */
    void on_resume(Event event);
    /*
     * Pause audio playback
     * This method pauses the audio playback if it has been resumed
     */
    void on_pause(Event event);

    /*
     * Select equalizer visualiser
     * This method changes the current visualiser to the equalizer visualiser
     */
    void on_equalizer_select(Event event);
    /*
     * Select circular visualiser
     * This method changes the current visualiser to the circular visualiser
     */
    void on_circular_select(Event event);
    /*
     * Select volumes visualiser
     * This method changes the current visualiser to the volumes visualiser
     */
    void on_volumes_select(Event event);

    /*
     * Initialize menu bar
     * This method initializes the native menu bar with all its options
     */
    void init_menu_bar();
};

#endif
