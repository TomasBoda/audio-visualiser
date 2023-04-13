#ifndef FFT_MUSIC_VISUALISER_CIRCULAR_H
#define FFT_MUSIC_VISUALISER_CIRCULAR_H

#include <wx/wx.h>
#include <string>
#include "../../../config/config.h"
#include "../../../utils/visualiser/Visualiser.h"

class Circular : public Visualiser {
public:
    Circular();

    void render(Graphics graphics) override;
    void update() override;
    void copy_frequency_spectrum() override;
    void init_default_frequency_spectrum() override;

private:
    double * frequency_spectrum;

    const double smoothing_factor = 10;

    const wxPen pen_inner_lines { wxColour(40, 40, 40), 1 };
    const wxPen pen_outer_lines { wxColour(255, 255, 255), 1 };
    const wxPen pen_inner_circle { wxColour(255, 255, 255), 5 };
    const wxBrush brush_inner_circle { wxColour(0, 0, 0) };

    void apply_gravity_to_frequency_spectrum();
    double normalize_frequency(double db_value) const;

    double index_to_angle(int index);

    wxPoint get_endpoint(wxPoint & center, double db, double angle_in_radians) const;
};

#endif
