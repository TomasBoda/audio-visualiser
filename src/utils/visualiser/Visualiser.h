#ifndef FFT_MUSIC_VISUALISER_VISUALISER_H
#define FFT_MUSIC_VISUALISER_VISUALISER_H

#include <wx/wx.h>
#include "../../config/config.h"

/*
 * Visualiser
 * This class represents a custom visualiser
 */
class Visualiser {
public:
    Visualiser();

    void render_visualiser(Graphics graphics);
    void update_visualiser();
protected:
    double * frequency_spectrum_left;
    double * frequency_spectrum_right;

    /*
     * Render the visualiser
     * This method renders the custom visualiser and its components
     * @param graphics graphics object @see wxDC
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
};

#endif
