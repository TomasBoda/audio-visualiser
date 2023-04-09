#ifndef FFT_MUSIC_VISUALISER_VISUALISER_H
#define FFT_MUSIC_VISUALISER_VISUALISER_H

#include <wx/wx.h>
#include "../../config/config.h"

class Visualiser {
public:
    Visualiser();

    void render_visualiser(wxDC & graphics);
    void update_visualiser();
protected:
    double * frequency_spectrum;

    virtual void render(wxDC & graphics) {}
    virtual void update() {}

    virtual void init_default_frequency_spectrum();
    virtual void copy_frequency_spectrum();
};

#endif
