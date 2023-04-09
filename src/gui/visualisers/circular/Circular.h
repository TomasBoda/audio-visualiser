#ifndef FFT_MUSIC_VISUALISER_CIRCULAR_H
#define FFT_MUSIC_VISUALISER_CIRCULAR_H

#include <wx/wx.h>
#include <string>
#include "../../../utils/visualiser/Visualiser.h"

class Circular : public Visualiser {
public:
    void render(wxDC & graphics) override;
    void update() override;
    void copy_frequency_spectrum() override;
    void init_default_frequency_spectrum() override;

private:
    const wxPen pen_inner_lines { wxColour(40, 40, 40), 3 };
    const wxPen pen_outer_lines { wxColour(255, 255, 255), 5 };
    const wxPen pen_inner_circle { wxColour(255, 255, 255), 5 };
    const wxBrush brush_inner_circle { wxColour(0, 0, 0) };

    void apply_gravity_to_frequency_spectrum();
    double normalize_frequency(double db_value) const;

    wxPoint get_endpoint(wxPoint & center, double db, double angle_in_radians) const;
};

#endif
