#ifndef FFT_MUSIC_VISUALISER_CIRCULAR_H
#define FFT_MUSIC_VISUALISER_CIRCULAR_H

#include <wx/wx.h>
#include <string>
#include "../../../config/config.h"
#include "../../../utils/visualiser/Visualiser.h"

/*
 * Circular visualiser derived from the generic visualiser
 */
class Circular : public Visualiser {
public:
    Circular();

    void render(Graphics graphics) override;
    void update() override;
    void copy_frequency_spectrum() override;
    void init_default_frequency_spectrum() override;

private:
    double_array frequency_spectrum;

    const double gravity = 0.015;
    const double smoothing_factor = 30;
    const int radius = 100;

    const wxPen pen_inner_lines { wxColour(40, 40, 40), 1 };
    const wxPen pen_outer_lines { wxColour(255, 255, 255), 3 };
    const wxPen pen_inner_circle { wxColour(255, 255, 255), 5 };
    const wxBrush brush_inner_circle { wxColour(0, 0, 0) };

    /*
     * Normalize frequencies
     * This method normalizes (scales) the frequency endpoints by a constant factor depending on the window height to fit into the screen
     * @param db_value decibel value of the frequency endpoint
     * @return normalized frequency value
     */
    double normalize_frequency(double db_value) const;
    /*
     * Apply gravity to frequencies
     * This method applies gravity to each frequency in the spectrum for smooth animation
     */
    void apply_gravity_to_frequency_spectrum();

    /*
     * Convert frequency index to angle
     * This method converts the index of the frequency in the frequency spectrum to angle in radians
     * @param index index of the frequency endpoint in the spectrum
     * @return angle in radians
     */
    double index_to_angle(int index) const;

    /*
     * Get endpoint position
     * This method calculates the position of an endpoints based on the center of the visualiser, decibel magnitude and angle in radians
     * @param center endpoint representing the center of the visualiser
     * @param db decibel magnitude of the frequency endpoint
     * @param angle_in_radians angle of the current frequency endpoints
     * @return wxPoint new point and its coordinates to be drawn
     */
    wxPoint get_endpoint(wxPoint & center, double db, double angle_in_radians) const;
};

#endif
