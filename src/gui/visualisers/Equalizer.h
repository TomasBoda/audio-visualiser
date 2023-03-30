#ifndef FFT_MUSIC_VISUALISER_EQUALIZER_H
#define FFT_MUSIC_VISUALISER_EQUALIZER_H

#include <wx/wx.h>
#include <string>
#include "../../utils/Visualiser.h"

class Equalizer : public Visualiser {
public:
    Equalizer() {
        num_of_parts = 4;
        spectrum = 20000.0;
        delimiters = new double[num_of_parts + 1] { 0, 200, 1000, 8000, 20000 };
        ranges = new double[num_of_parts] { delimiters[1] - delimiters[0], delimiters[2] - delimiters[1], delimiters[3] - delimiters[2], delimiters[4] - delimiters[3] };
        factors = new double[num_of_parts] { spectrum / ranges[0], spectrum / ranges[1], spectrum / ranges[2], spectrum / ranges[3] };
        indexes = new double[num_of_parts + 1] { 0, global::NUM_CHUNKS / factors[0], global::NUM_CHUNKS / factors[1], global::NUM_CHUNKS / factors[2], global::NUM_CHUNKS / factors[3] };
    }

    void render(wxPaintDC & graphics) override {
        widths = new double[num_of_parts] { global::WIDTH / 10.0 * 2.0, global::WIDTH / 10.0 * 2.0, global::WIDTH / 10.0 * 3.0, global::WIDTH / 10.0 * 3.0 };

        draw_frequency_lines(graphics);
        draw_middle_line(graphics);
        draw_frequency_texts(graphics);
    }

    void update() override {
        apply_gravity_to_frequency_spectrum();
    }

    void copy_frequency_spectrum() override {
        std::lock_guard<std::mutex> lock(global::MUTEX);

        for (int i = 0; i < global::NUM_CHUNKS; i++) {
            double fft_value = global::SPECTRUM[i];
            double frq_value = frequency_spectrum[i];

            if (normalize_frequency(fft_value) > frq_value) {
                frequency_spectrum[i] = normalize_frequency(fft_value);
            }
        }
    }

    void init_default_frequency_spectrum() override {
        for (int i = 0; i < global::NUM_CHUNKS; i++) {
            frequency_spectrum[i] = global::HEIGHT;
        }
    }

private:
    int num_of_parts;
    double spectrum;
    double * delimiters;
    double * ranges;
    double * factors;
    double * indexes;
    double * widths;

    wxPen pen_frequency_line { wxColour(255, 255, 255), 2 };
    wxPen pen_middle_line { wxColour(90, 90, 90), 2 };
    wxFont font_frequency_text { 15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial") };

    double normalize_frequency(double db_value) {
        double db_range = 60;
        double pixel_factor = global::HEIGHT / db_range;
        return db_value * pixel_factor;
    }

    void apply_gravity_to_frequency_spectrum() {
        for (int i = 0; i < global::NUM_CHUNKS; i++) {
            frequency_spectrum[i] -= global::GRAVITY;
        }
    }

    void draw_frequency_texts(wxPaintDC & graphics) {
        graphics.SetFont(font_frequency_text);

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

    void draw_middle_line(wxPaintDC & graphics) {
        graphics.SetPen(pen_middle_line);
        graphics.DrawLine(0, global::HEIGHT / 2, global::WIDTH, global::HEIGHT / 2);
    }

    void draw_frequency_lines(wxPaintDC & graphics) {
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

    void draw_frequency_line(wxPaintDC & graphics, int x1, int y1, int x2, int y2) {
        double factor = (255.0 / global::WIDTH) * x1;
        double r = factor;
        double g = 0;
        double b = 255 - factor;

        graphics.SetPen(wxPen(wxColour(r, g, b), 5));
        graphics.DrawLine(x1, y1, x2, y2);
    }
};

#endif
