
#include "Window.h"
#include <wx/wx.h>
#include <cmath>

using namespace std;

void Window::draw_spectrum_visualisation(wxPaintEvent &event) {
    wxPaintDC graphics(this);

    for (int i = 0; i < global::NUM_CHUNKS; i++) {
        auto height = frequency_spectrum[i];
        int width = global::WIDTH / global::NUM_CHUNKS;

        int x = i * width;
        int y = global::HEIGHT - height;

        int factor = 255 / global::NUM_CHUNKS * i;
        int r = factor;
        int g = 0;
        int b = 255 - factor;

        graphics.SetBrush(wxBrush(wxColour(r, g, b)));
        graphics.DrawRectangle(x, y, width, height);
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
        double new_frequency = 0;

        for (int j = 0; j < global::SMOOTHING_FACTOR; j++) {
            int index = (i + j) % global::NUM_CHUNKS;
            new_frequency += global::SPECTRUM[index];
        }

        new_frequency /= global::SMOOTHING_FACTOR;

        if (new_frequency > frequency_spectrum[i]) {
            frequency_spectrum[i] = new_frequency;
        }
    }
}

void Window::apply_gravity_to_frequency_spectrum() {
    for (int i = 0; i < global::NUM_CHUNKS; i++) {
        double offset = frequency_spectrum[i] * global::GRAVITY;
        frequency_spectrum[i] -= offset;
    }
}
