#include "Circular.h"

Circular::Circular(): frequency_spectrum(std::make_unique<double[]>(global::NUM_CHUNKS * 2)) {}

void Circular::render(Graphics graphics) {
    wxPoint center(global::WIDTH / 2, global::HEIGHT / 5 * 3);

    for (int i = 0; i < global::NUM_CHUNKS * 2; i++) {
        int i1 = (i) % (global::NUM_CHUNKS * 2);
        int i2 = (i + 1) % (global::NUM_CHUNKS * 2);

        double db1 = frequency_spectrum[i1];
        double db2 = frequency_spectrum[i2];

        double angle1 = index_to_angle(i1);
        double angle2 = index_to_angle(i2);

        wxPoint s1 = get_endpoint(center, radius, angle1);
        wxPoint s2 = get_endpoint(center, radius, angle2);

        wxPoint p1 = get_endpoint(s1, db1, angle1);
        wxPoint p2 = get_endpoint(s2, db2, angle2);

        // inner lines
        if (i % 6 == 0) {
            graphics.SetPen(pen_inner_lines);
            graphics.DrawLine(center, p1);
            graphics.DrawLine(center, p2);
        }

        // outer connected line
        graphics.SetPen(pen_outer_lines);
        graphics.DrawLine(p1, p2);
    }

    // inner circle
    graphics.SetBrush(brush_inner_circle);
    graphics.SetPen(pen_inner_circle);
    graphics.DrawCircle(center, radius);
}

void Circular::update() {
    apply_gravity_to_frequency_spectrum();
}

void Circular::copy_frequency_spectrum() {
    std::lock_guard<std::mutex> lock(global::MUTEX);

    for (int i = 0; i < global::NUM_CHUNKS * 2; i++) {
        double new_frequency = 0;

        for (int j = 0; j < smoothing_factor; j++) {
            const int index = (i + j) % (global::NUM_CHUNKS * 2);
            const int index_reversed = global::NUM_CHUNKS - (index % global::NUM_CHUNKS) - 1;

            if (index < global::NUM_CHUNKS) {
                new_frequency += normalize_frequency(global::SPECTRUM_LEFT[index]);
            } else {
                new_frequency += normalize_frequency(global::SPECTRUM_RIGHT[index_reversed]);
            }
        }

        new_frequency /= smoothing_factor;

        // update the frequency only if the new frequency is higher in volume than the previous one
        // this ensures smooth gravity animation
        if (new_frequency > frequency_spectrum[i]) {
            frequency_spectrum[i] = new_frequency;
        }
    }
}

void Circular::init_default_frequency_spectrum() {
    for (int i = 0; i < global::NUM_CHUNKS * 2; i++) {
        frequency_spectrum[i] = global::HEIGHT;
    }
}

void Circular::apply_gravity_to_frequency_spectrum() {
    for (int i = 0; i < global::NUM_CHUNKS * 2; i++) {
        double offset = frequency_spectrum[i] * gravity;
        frequency_spectrum[i] -= offset;
    }
}

double Circular::normalize_frequency(double db_value) const {
    const double db_range = 40;
    const double pixel_factor = (double) global::HEIGHT / 2.0 / db_range;
    return db_value * pixel_factor;
}

double Circular::index_to_angle(int index) const {
    const double offset = -90;
    return ((double) index * (360.0 / (global::NUM_CHUNKS * 2)) + offset + ((smoothing_factor - 1) / 4)) * (M_PI / 180);
}

wxPoint Circular::get_endpoint(wxPoint &center, double db, double angle_in_radians) const {
    const double x = (double) center.x + db * cos(angle_in_radians);
    const double y = (double) center.y + db * sin(angle_in_radians);
    return wxPoint(x, y);
}