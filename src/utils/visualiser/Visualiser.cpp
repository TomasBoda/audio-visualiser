#include <wx/wx.h>
#include "../../config/config.h"
#include "Visualiser.h"

Visualiser::Visualiser(): frequency_spectrum(new double[global::NUM_CHUNKS]) {
    init_default_frequency_spectrum();
}

void Visualiser::render_visualiser(wxDC &graphics) {
    render(graphics);
}

void Visualiser::update_visualiser() {
    copy_frequency_spectrum();
    update();
}

void Visualiser::init_default_frequency_spectrum() {
    for (int i = 0; i < global::NUM_CHUNKS; i++) {
        frequency_spectrum[i] = 0;
    }
}

void Visualiser::copy_frequency_spectrum() {
    std::lock_guard<std::mutex> lock(global::MUTEX);

    for (int i = 0; i < global::NUM_CHUNKS; i++) {
        frequency_spectrum[i] = global::SPECTRUM[i];
    }
}