#ifndef FFT_MUSIC_VISUALISER_VISUALISER_H
#define FFT_MUSIC_VISUALISER_VISUALISER_H

#include <wx/wx.h>
#include "../../config/config.h"
#include "../time/Time.h"

/*
 * Visualiser
 * This class represents a custom visualiser
 */
class Visualiser {
public:
    Visualiser();

    /*
     * Render visualiser
     * This method render the visualiser
     */
    void render_visualiser(Graphics graphics);
    /*
     * Update visualiser
     * This method updates the visualizer
     */
    void update_visualiser();
protected:
    double_array frequency_spectrum_left;
    double_array frequency_spectrum_right;

    int total_time;
    int remaining_time;

    /*
     * Render the visualiser
     * This method renders the custom visualiser and its components
     */
    virtual void render(Graphics graphics) {}
    /*
     * Update the visualiser
     * This method updates the custom visualiser and its components
     */
    virtual void update() {}

    /*
     * Initialize default frequency spectrum values
     * This method initializes the default values of the frequency spectrum
     */
    virtual void init_default_frequency_spectrum();
    /*
     * Copy frequency spectrum from audio stream
     * This method copies the frequency spectrum from the audio thread
     */
    virtual void copy_frequency_spectrum();

    /*
     * Update the remaining audio playback time
     * This method calculates the remaining audio playback time
     */
    void update_remaining_time();
    /*
     * Render the remaining audio playback time
     * This method renders the remaining audio playback time
     */
    void render_remaining_time(Graphics graphics);
};

#endif
