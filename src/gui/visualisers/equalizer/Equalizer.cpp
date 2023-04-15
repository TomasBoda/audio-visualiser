#include "Equalizer.h"

Equalizer::Equalizer(): num_of_parts(4), hz_range(20000.0) {
    delimiters = double_vector{ 0, 200, 1000, 8000, 20000};
    indexes = double_vector{ 0,
        global::NUM_CHUNKS / (hz_range / (delimiters[1] - delimiters[0])),
        global::NUM_CHUNKS / (hz_range / (delimiters[2] - delimiters[1])),
        global::NUM_CHUNKS / (hz_range / (delimiters[3] - delimiters[2])),
        global::NUM_CHUNKS / (hz_range / (delimiters[4] - delimiters[3])) };
    update_widths();
}

void Equalizer::render(Graphics graphics) {
    draw_frequency_lines(graphics, frequency_spectrum_left, colour_spectrum_left);
    draw_frequency_lines(graphics, frequency_spectrum_right, colour_spectrum_right);
    draw_middle_line(graphics);
    draw_frequency_texts(graphics);
    draw_hints(graphics);
}

void Equalizer::update() {
    update_widths();
    apply_gravity_to_frequency_spectrum();
}

void Equalizer::copy_frequency_spectrum() {
    std::lock_guard<std::mutex> lock(global::MUTEX);

    for (int i = 0; i < global::NUM_CHUNKS; i++) {
        double fft_value_left = global::SPECTRUM_LEFT[i];
        double fft_value_right = global::SPECTRUM_RIGHT[i];

        double frq_value_left = frequency_spectrum_left[i];
        double frq_value_right = frequency_spectrum_right[i];

        if (normalize_frequency(fft_value_left) > frq_value_left) {
            frequency_spectrum_left[i] = normalize_frequency(fft_value_left);
        }

        if (normalize_frequency(fft_value_right) > frq_value_right) {
            frequency_spectrum_right[i] = normalize_frequency(fft_value_right);
        }
    }
}

void Equalizer::init_default_frequency_spectrum() {
    for (int i = 0; i < global::NUM_CHUNKS; i++) {
        frequency_spectrum_left[i] = global::HEIGHT;
        frequency_spectrum_right[i] = global::HEIGHT;
    }
}

double Equalizer::normalize_frequency(double db_value) const {
    const double db_range = 60;
    const double pixel_factor = global::HEIGHT / db_range;
    return db_value * pixel_factor;
}

void Equalizer::apply_gravity_to_frequency_spectrum() {
    for (int i = 0; i < global::NUM_CHUNKS; i++) {
        frequency_spectrum_left[i] -= gravity;
        frequency_spectrum_right[i] -= gravity;
    }
}

void Equalizer::draw_frequency_texts(Graphics graphics) {
    graphics.SetFont(font_frequency_text);
    graphics.SetTextForeground(wxColour(255, 255, 255));

    for (int i = 0; i < num_of_parts + 1; i++) {
        double offset = 0;
        for (int j = 0; j < i - 1; j++) offset += widths[j];

        wxString value = std::to_string((int) delimiters[i]) + " Hz";
        int x = offset + (i == 0 ? 0 : widths[i - 1]);
        int y = global::HEIGHT / 2 + 30;

        if (i == 0) x += 30;
        if (i == 4) x -= 100;

        graphics.DrawText(value, x, y);

        graphics.SetPen(wxPen(wxColour(90, 90, 90), 2));
        graphics.DrawLine(x, global::HEIGHT / 2 - 10, x, global::HEIGHT / 2 + 10);

        if (i > 0) {
            wxString value_mid = std::to_string((int) ((delimiters[i] + delimiters[i - 1]) / 2)) + " Hz";
            int x_mid = offset + widths[i - 1] / 2;
            graphics.DrawText(value_mid, x_mid, y);
            graphics.DrawLine(x_mid, global::HEIGHT / 2 - 10, x_mid, global::HEIGHT / 2 + 10);
        }
    }
}

void Equalizer::draw_middle_line(Graphics graphics) {
    graphics.SetPen(pen_middle_line);
    graphics.DrawLine(0, global::HEIGHT / 2, global::WIDTH, global::HEIGHT / 2);
}

void Equalizer::draw_frequency_lines(Graphics graphics, double_array & frequency_spectrum, const wxColour & colour) {
    int x_prev = 0;
    int y_prev = global::HEIGHT;

    for (int i = 0; i < num_of_parts; i++) {
        double offset = 0;
        for (int j = 0; j < i; j++) offset += widths[j];

        for (int j = indexes[i]; j < indexes[i + 1]; j++) {
            double height = frequency_spectrum[j];
            double width = widths[i] / (indexes[i + 1] - indexes[i]);

            int x = offset + (j - indexes[i]) * width;
            int y = global::HEIGHT - height;

            if (!(i == 0 && j == indexes[0])) {
                draw_frequency_line(graphics, x_prev, y_prev, x, y, colour);
            }

            x_prev = x;
            y_prev = y;
        }
    }
}

void Equalizer::draw_frequency_line(Graphics graphics, int x1, int y1, int x2, int y2, const wxColour & colour) {
    graphics.SetPen(wxPen(colour, 5));
    graphics.DrawLine(x1, y1, x2, y2);
}

void Equalizer::draw_hints(Graphics graphics) {
    graphics.SetPen(wxPen(colour_spectrum_left, 5));
    graphics.DrawLine(50, 50, 100, 50);

    graphics.SetPen(wxPen(colour_spectrum_right, 5));
    graphics.DrawLine(50, 80, 100, 80);

    graphics.SetFont(font_frequency_text);
    graphics.SetTextForeground(wxColour(255, 255, 255));

    graphics.DrawText("Left Channel", 120, 42);
    graphics.DrawText("Right Channel", 120, 72);
}

void Equalizer::update_widths() {
    widths = double_vector{ global::WIDTH / 10.0 * 2.0, global::WIDTH / 10.0 * 2.0, global::WIDTH / 10.0 * 3.0, global::WIDTH / 10.0 * 3.0 };
}