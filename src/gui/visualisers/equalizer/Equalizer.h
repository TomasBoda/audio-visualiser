#ifndef FFT_MUSIC_VISUALISER_EQUALIZER_H
#define FFT_MUSIC_VISUALISER_EQUALIZER_H

#include <wx/wx.h>
#include <string>
#include <mutex>
#include <memory>
#include <vector>
#include "../../../config/config.h"
#include "../../../utils/visualiser/Visualiser.h"

/*
 * Equalizer visualiser derived from the generic visualiser
 */
class Equalizer : public Visualiser {
public:
    Equalizer();

    void render(Graphics graphics) override;
    void update() override;
    void copy_frequency_spectrum() override;
    void init_default_frequency_spectrum() override;
private:
    const double gravity = 3;

    int num_of_parts;
    double hz_range;

    double_vector delimiters;
    double_vector indexes;
    double_vector widths;

    const wxColour colour_spectrum_left{232, 80, 53};
    const wxColour colour_spectrum_right{78, 118, 230};

    const wxPen pen_frequency_line { wxColour(255, 255, 255), 2 };
    const wxPen pen_middle_line { wxColour(90, 90, 90), 2 };
    const wxFont font_frequency_text { 15, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Arial") };

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
     * Draw frequency texts
     * This method draws the frequency spectrum breakpoints with their values in Hz
     */
    void draw_frequency_texts(Graphics graphics);
    /*
     * Draw middle line
     * This method draws the middle horizontal line
     */
    void draw_middle_line(Graphics graphics);
    /*
     * Draw frequency lines
     * This method draws the frequency lines between each two frequency decibel endpoints
     */
    void draw_frequency_lines(Graphics graphics, double_array & frequency_spectrum, const wxColour & colour);
    /*
     * Draw frequency line
     * This method draws a frequency line between two frequency decibel endpoints
     */
    void draw_frequency_line(Graphics graphics, int x1, int y1, int x2, int y2, const wxColour & colour);
    /*
     * Draw hints
     * This method draws hints for the user
     */
    void draw_hints(Graphics graphics);

    /*
     * Update widths
     * This method updates the widths of frequency bands based on current window width
     */
    void update_widths();
};

#endif
