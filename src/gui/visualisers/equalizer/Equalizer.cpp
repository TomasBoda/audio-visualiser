#include "Equalizer.h"

Equalizer::Equalizer() {
    num_of_parts = 4;
    spectrum = 20000.0;
    delimiters = new double[num_of_parts + 1] { 0, 200, 1000, 8000, 20000 };
    ranges = new double[num_of_parts] { delimiters[1] - delimiters[0], delimiters[2] - delimiters[1], delimiters[3] - delimiters[2], delimiters[4] - delimiters[3] };
    factors = new double[num_of_parts] { spectrum / ranges[0], spectrum / ranges[1], spectrum / ranges[2], spectrum / ranges[3] };
    indexes = new double[num_of_parts + 1] { 0, global::NUM_CHUNKS / factors[0], global::NUM_CHUNKS / factors[1], global::NUM_CHUNKS / factors[2], global::NUM_CHUNKS / factors[3] };
    widths = new double[num_of_parts] { global::WIDTH / 10.0 * 2.0, global::WIDTH / 10.0 * 2.0, global::WIDTH / 10.0 * 3.0, global::WIDTH / 10.0 * 3.0 };
}

void Equalizer::render(Graphics graphics) {
    draw_frequency_lines(graphics);
    draw_middle_line(graphics);
    draw_frequency_texts(graphics);
}

void Equalizer::update() {
    widths = new double[num_of_parts] { global::WIDTH / 10.0 * 2.0, global::WIDTH / 10.0 * 2.0, global::WIDTH / 10.0 * 3.0, global::WIDTH / 10.0 * 3.0 };
    apply_gravity_to_frequency_spectrum();
}

void Equalizer::copy_frequency_spectrum() {
    std::lock_guard<std::mutex> lock(global::MUTEX);

    for (int i = 0; i < global::NUM_CHUNKS; i++) {
        double fft_value = global::SPECTRUM[i];
        double frq_value = frequency_spectrum[i];

        if (normalize_frequency(fft_value) > frq_value) {
            frequency_spectrum[i] = normalize_frequency(fft_value);
        }
    }
}

void Equalizer::init_default_frequency_spectrum() {
    for (int i = 0; i < global::NUM_CHUNKS; i++) {
        frequency_spectrum[i] = global::HEIGHT;
    }
}

double Equalizer::normalize_frequency(double db_value) {
    double db_range = 60;
    double pixel_factor = global::HEIGHT / db_range;
    return db_value * pixel_factor;
}

void Equalizer::apply_gravity_to_frequency_spectrum() {
    for (int i = 0; i < global::NUM_CHUNKS; i++) {
        frequency_spectrum[i] -= gravity;
    }
}

void Equalizer::draw_frequency_texts(Graphics graphics) {
    graphics.SetFont(font_frequency_text);
    graphics.SetTextForeground(wxColour(255, 255, 255));

    for (int i = 0; i < 5; i++) {
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

void Equalizer::draw_frequency_lines(Graphics graphics) {
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
                draw_frequency_line(graphics, x_prev, y_prev, x, y);
            }

            x_prev = x;
            y_prev = y;
        }
    }
}

void Equalizer::draw_frequency_line(Graphics graphics, int x1, int y1, int x2, int y2) {
    double factor = (255.0 / global::WIDTH) * x1;
    double r = factor;
    double g = 0;
    double b = 255 - factor;

    graphics.SetPen(wxPen(wxColour(r, g, b), 5));
    graphics.DrawLine(x1, y1, x2, y2);
}