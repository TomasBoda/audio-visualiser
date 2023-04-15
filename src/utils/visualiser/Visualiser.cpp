#include "Visualiser.h"

Visualiser::Visualiser():
    frequency_spectrum_left(std::make_unique<double[]>(global::NUM_CHUNKS)),
    frequency_spectrum_right(std::make_unique<double[]>(global::NUM_CHUNKS))
{
    init_default_frequency_spectrum();
}

void Visualiser::render_visualiser(Graphics graphics) {
    render(graphics);
}

void Visualiser::update_visualiser() {
    copy_frequency_spectrum();
    update();
}

void Visualiser::init_default_frequency_spectrum() {
    for (int i = 0; i < global::NUM_CHUNKS; i++) {
        frequency_spectrum_left[i] = 0;
        frequency_spectrum_right[i] = 0;
    }
}

void Visualiser::copy_frequency_spectrum() {
    std::lock_guard<std::mutex> lock(global::MUTEX);

    for (int i = 0; i < global::NUM_CHUNKS; i++) {
        frequency_spectrum_left[i] = global::SPECTRUM_LEFT[i];
        frequency_spectrum_right[i] = global::SPECTRUM_RIGHT[i];
    }
}