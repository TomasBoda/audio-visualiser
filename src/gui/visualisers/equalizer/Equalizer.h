#ifndef FFT_MUSIC_VISUALISER_EQUALIZER_H
#define FFT_MUSIC_VISUALISER_EQUALIZER_H

#include <wx/wx.h>
#include <string>
#include <mutex>
#include <memory>
#include <vector>
#include "../../../config/config.h"
#include "../../../utils/visualiser/Visualiser.h"

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

    double normalize_frequency(double db_value) const;
    void apply_gravity_to_frequency_spectrum();

    void draw_frequency_texts(Graphics graphics);
    void draw_middle_line(Graphics graphics);
    void draw_frequency_lines(Graphics graphics, double_array & frequency_spectrum, const wxColour & colour);
    void draw_frequency_line(Graphics graphics, int x1, int y1, int x2, int y2, const wxColour & colour);
    void draw_hints(Graphics graphics);

    void update_widths();
};

#endif
