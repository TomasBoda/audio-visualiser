#ifndef FFT_MUSIC_VISUALISER_VOLUMES_H
#define FFT_MUSIC_VISUALISER_VOLUMES_H

#include "wx/wx.h"
#include <string>
#include "../../../config/config.h"
#include "../../../utils/visualiser/Visualiser.h"

class Volumes : public Visualiser {
public:
    Volumes();

    void render(Graphics graphics) override;
    void update() override;
private:
    int num_seconds = global::VOLUME_LEVELS.size();

    double scaling_factor;

    int x_window;
    int width_window;
    int height_window;

    int pointer_position;

    wxPen pen_pointer{wxColour(47, 113, 212), 5};
    wxPen pen_volumes{wxColour(255, 255, 255), 1};
    wxBrush brush_volumes{wxColour(0, 0, 0)};

    /*
     * Draws volume bars
     * This method draws volume bars onto the window
     */
    void draw_volumes(Graphics graphics);
    /*
     * Draws pointer
     * This method draws duration pointer onto the window
     */
    void draw_pointer(Graphics graphics);

    /*
     * Update pointer position
     * This method recalculates the duration pointer position
     */
    void update_pointer_position();

    /*
     * Update visualisation dimensions
     * This method updates the visualiser window dimensions based on window dimensions
     */
    void update_display_window();
    /*
     * Update scaling factor
     * This method updates the scaling factor of the volume bars to fit onto the screen
     */
    double get_scaling_factor();
};

#endif