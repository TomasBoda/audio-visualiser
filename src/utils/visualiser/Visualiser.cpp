#include "Visualiser.h"

Visualiser::Visualiser():
    frequency_spectrum_left(std::make_unique<double[]>(global::NUM_CHUNKS)),
    frequency_spectrum_right(std::make_unique<double[]>(global::NUM_CHUNKS)),
    total_time(global::VOLUME_LEVELS.size())
{
    init_default_frequency_spectrum();
}

void Visualiser::render_visualiser(Graphics graphics) {
    render(graphics);
    render_remaining_time(graphics);
}

void Visualiser::update_visualiser() {
    copy_frequency_spectrum();
    update_remaining_time();
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

void Visualiser::update_remaining_time() {
    remaining_time = (double) global::AUDIO_POSITION / (double) global::AUDIO_SIZE * (double) total_time;
}

void Visualiser::render_remaining_time(Graphics graphics) {
    graphics.SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial")));
    graphics.SetTextForeground(wxColour(255, 255, 255));

    time_pair total_time_in_minutes = seconds_to_minutes(total_time);
    time_pair remaining_time_in_minutes = seconds_to_minutes(remaining_time);

    std::string total_time_string = time_to_string(total_time_in_minutes);
    std::string remaining_time_string = time_to_string(remaining_time_in_minutes);

    std::string time_string = remaining_time_string + " / " + total_time_string;

    graphics.DrawText(time_string, global::WIDTH - 165, 40);
}