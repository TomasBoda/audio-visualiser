#ifndef FFT_MUSIC_VISUALISER_VISUALISER_H
#define FFT_MUSIC_VISUALISER_VISUALISER_H

#include <wx/wx.h>
#include "../config.h"

class Visualiser {
public:
    Visualiser(): frequency_spectrum(new double[global::NUM_CHUNKS]) {
        init_default_frequency_spectrum();
    }

    void render_visualiser(wxPaintDC & graphics) {
        render(graphics);
    }

    void update_visualiser() {
        copy_frequency_spectrum();
        update();
    }

protected:
    double * frequency_spectrum;

    virtual void render(wxPaintDC & graphics) {}
    virtual void update() {}

    virtual void init_default_frequency_spectrum() {
        for (int i = 0; i < global::NUM_CHUNKS; i++) {
            frequency_spectrum[i] = 0;
        }
    }

    virtual void copy_frequency_spectrum() {
        std::lock_guard<std::mutex> lock(global::MUTEX);

        for (int i = 0; i < global::NUM_CHUNKS; i++) {
            frequency_spectrum[i] = global::SPECTRUM[i];
        }
    }
};

#endif
