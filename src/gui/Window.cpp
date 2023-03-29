
#include "Window.h"
#include <wx/wx.h>
#include <cmath>

using namespace std;

void Window::draw_spectrum_visualisation(wxPaintEvent &event) {
    wxPaintDC graphics(this);

    int size = global::NUM_CHUNKS;

    double spectrum = 20000.0;
    double freqs[] = { 0, 200, 1000, 8000, 20000 };
    double frequencies[] = { freqs[1] - freqs[0], freqs[2] - freqs[1], freqs[3] - freqs[2], freqs[4] - freqs[3] };
    double ranges[] = { spectrum / frequencies[0], spectrum / frequencies[1], spectrum / frequencies[2], spectrum / frequencies[3] };

    double indexes[] = {0, size / ranges[0], size / ranges[1], size / ranges[2], size / ranges[3]};
    double widths[] = { global::WIDTH / 10.0 * 2.0, global::WIDTH / 10.0 * 2.0, global::WIDTH / 10.0 * 3.0, global::WIDTH / 10.0 * 3.0 };

    int x_prev = 0;
    int y_prev = global::HEIGHT;

    for (int i = 0; i < 4; i++) {
        double offset = 0;
        for (int j = 0; j < i; j++) offset += widths[j];

        for (int j = indexes[i]; j < indexes[i + 1]; j++) {
            double height = frequency_spectrum[j];
            double width = widths[i] / (indexes[i + 1] - indexes[i]);

            int x = offset + (j - indexes[i]) * width;
            int y = global::HEIGHT - height;

            if (!(i == 0 && j == indexes[0])) {
                graphics.SetPen(wxPen(wxColour(255, 255, 255), 2));
                graphics.DrawLine(x_prev, y_prev, x, y);
            }

            x_prev = x;
            y_prev = y;
        }
    }

    graphics.SetPen(wxPen(wxColour(90, 90, 90), 2));
    graphics.DrawLine(0, global::HEIGHT / 2, global::WIDTH, global::HEIGHT / 2);

    wxFont font = wxFont( 15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial") );
    graphics.SetFont(font);

    for (int i = 0; i < 5; i++) {
        double offset = 0;
        for (int j = 0; j < i - 1; j++) offset += widths[j];

        wxString value = to_string((int) freqs[i]) + " Hz";
        int x = offset + (i == 0 ? 0 : widths[i - 1]);
        int y = global::HEIGHT / 2 + 30;

        if (i == 0) {
            x += 30;
        } else if (i == 4) {
            x -= 100;
        }

        graphics.DrawText(value, x, y);

        graphics.SetPen(wxPen(wxColour(90, 90, 90), 2));
        graphics.DrawLine(x, global::HEIGHT / 2 - 10, x, global::HEIGHT / 2 + 10);

        if (i > 0) {
            wxString value_mid = to_string((int) ((freqs[i] + freqs[i - 1]) / 2)) + " Hz";
            int x_mid = offset + widths[i - 1] / 2;
            graphics.DrawText(value_mid, x_mid, y);
            graphics.DrawLine(x_mid, global::HEIGHT / 2 - 10, x_mid, global::HEIGHT / 2 + 10);
        }
    }
}

wxPoint get_endpoint(wxPoint & center, double db, double angle_in_radians) {
    double x = center.x + db * cos(angle_in_radians);
    double y = center.y + db * sin(angle_in_radians);
    return wxPoint(x, y);
}

void Window::draw_circle_visualisation(wxPaintEvent &event) {
    wxPaintDC graphics(this);

    wxPoint center(global::WIDTH / 2, global::HEIGHT / 2);
    double radius = 100;

    for (int i = 0; i < global::NUM_CHUNKS + 1; i++) {
        int i1 = i % global::NUM_CHUNKS;
        int i2 = (i + 1) % global::NUM_CHUNKS;

        double db1 = frequency_spectrum[i1];
        double db2 = frequency_spectrum[i2];

        double angle1 = i1 * (360 / global::NUM_CHUNKS) * (M_PI / 180);
        double angle2 = i2 * (360 / global::NUM_CHUNKS) * (M_PI / 180);

        wxPoint s1 = get_endpoint(center, radius, angle1);
        wxPoint s2 = get_endpoint(center, radius, angle2);

        wxPoint p1 = get_endpoint(s1, db1, angle1);
        wxPoint p2 = get_endpoint(s2, db2, angle2);

        // inner lines
        graphics.SetPen(pen_inner_lines);
        graphics.DrawLine(center, p1);
        graphics.DrawLine(center, p2);

        // outer connected line
        graphics.SetPen(pen_outer_lines);
        graphics.DrawLine(p1, p2);
    }

    // inner circle
    graphics.SetBrush(brush_inner_circle);
    graphics.SetPen(pen_inner_circle);
    graphics.DrawCircle(center, radius);
}

void Window::copy_and_normalize_frequency_spectrum() {
    std::lock_guard<std::mutex> lock(global::MUTEX);

    for (int i = 0; i < global::NUM_CHUNKS; i++) {
        if (global::SPECTRUM[i] > frequency_spectrum[i]) {
            frequency_spectrum[i] = global::SPECTRUM[i];
        }
    }
}

void Window::apply_gravity_to_frequency_spectrum() {
    for (int i = 0; i < global::NUM_CHUNKS; i++) {
        frequency_spectrum[i] -= global::GRAVITY;
    }
}
