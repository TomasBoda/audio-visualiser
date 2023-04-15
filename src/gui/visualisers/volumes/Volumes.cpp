#include "Volumes.h"

Volumes::Volumes(): num_seconds(global::VOLUME_LEVELS.size()) {
    update_display_window();
    update_scaling_factor();
}

void Volumes::render(Graphics graphics) {
    draw_volumes(graphics);
    draw_pointer(graphics);
}

void Volumes::update() {
    update_display_window();
    update_pointer_position();
    update_scaling_factor();
}

void Volumes::draw_volumes(Graphics graphics) {
    graphics.SetPen(pen_volumes);
    graphics.SetBrush(brush_volumes);

    double bar_width = (double) width_window / (double) num_seconds;

    for (int i = 0; i < num_seconds; i++) {
        double bar_height = global::VOLUME_LEVELS[i] * scaling_factor;
        int x = x_window + i * bar_width;
        int y = global::HEIGHT / 2 - bar_height / 2;

        graphics.DrawRectangle(x, y, bar_width, bar_height);
    }
}

void Volumes::draw_pointer(Graphics graphics) {
    graphics.SetPen(pen_pointer);
    graphics.DrawRectangle(pointer_position, global::HEIGHT / 2 - global::MAX_VOLUME * scaling_factor / 2 - 50, 5, global::MAX_VOLUME * scaling_factor + 100);
}

void Volumes::update_pointer_position() {
    const int size = global::AUDIO_SIZE;
    const int position = global::AUDIO_POSITION;
    double current_position = (double) position / (double) size;
    pointer_position = x_window + current_position * width_window;
}

void Volumes::update_display_window() {
    width_window = global::WIDTH < 800 ? global::WIDTH : global::WIDTH - 200;
    height_window = global::HEIGHT > 400 ? 400 : global::HEIGHT;
    x_window = global::WIDTH / 2 - width_window / 2;
}

void Volumes::update_scaling_factor() {
    scaling_factor = height_window / global::MAX_VOLUME;
}
