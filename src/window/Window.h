#include <iostream>
#include <vector>
#include <wx/wx.h>
#include <algorithm>
#include "../config.h"

#ifndef FFT_MUSIC_VISUALISER_WINDOW_H
#define FFT_MUSIC_VISUALISER_WINDOW_H

class Window : public wxFrame {
public:
    Window(const wxString & title, const wxPoint & pos, const wxSize & size) : wxFrame(NULL, wxID_ANY, title, pos, size) {
        timer = new wxTimer(this, wxID_ANY);

        Bind(wxEVT_TIMER, &Window::OnTimer, this, timer->GetId());
        Bind(wxEVT_PAINT, &Window::OnPaint, this);

        timer->Start(20);

        SetBackgroundColour(wxColour(* wxBLACK));
        SetSize(size);
        SetPosition(pos);
        Show(true);
    };

    ~Window() {
        timer->Stop();
        delete timer;
    }

    void OnClose(wxCloseEvent& event) {
        timer->Stop();
        Destroy();
    }

    void OnTimer(wxTimerEvent& event) {
        Refresh();
    }

    void OnPaint(wxPaintEvent& event) {
        wxPaintDC dc(this);

        std::lock_guard<std::mutex> lock(global::MUTEX);

        for (int i = 0; i < global::NUM_CHUNKS; i++) {
            auto magnitude = global::SPECTRUM[i];

            double x_c = global::WIDTH / 2;
            double y_c = global::HEIGHT / 2;

            double x_m = 0;
            double y_m = 0;

            double degrees = i * (360 / global::NUM_CHUNKS);

            if (degrees <= 90) {
                double angle = degrees * (M_PI / 180.0);

                double vertical_length = std::cos(angle) * magnitude;
                double horizontal_length = std::sin(angle) * magnitude;

                x_m = x_c + horizontal_length;
                y_m = y_c - vertical_length;
            } else if (degrees > 90 && degrees <= 180) {
                double angle = (degrees - 90) * (M_PI / 180.0);

                double vertical_length = std::cos(angle) * magnitude;
                double horizontal_length = std::sin(angle) * magnitude;

                x_m = x_c + horizontal_length;
                y_m = y_c + vertical_length;
            } else if (degrees > 180 && degrees <= 270) {
                double angle = (degrees - 180) * (M_PI / 180.0);

                double vertical_length = std::cos(angle) * magnitude;
                double horizontal_length = std::sin(angle) * magnitude;

                x_m = x_c - horizontal_length;
                y_m = y_c + vertical_length;
            } else if (degrees > 270) {
                double angle = (degrees - 270) * (M_PI / 180.0);

                double vertical_length = std::cos(angle) * magnitude;
                double horizontal_length = std::sin(angle) * magnitude;

                x_m = x_c - horizontal_length;
                y_m = y_c - vertical_length;
            }

            int red = std::min((int) magnitude, 255);
            int green = std::min((int) (degrees / 1.5), 255);
            int blue = 255 - std::min((int) magnitude, 255);

            int stroke = 20;

            wxPen pen(wxColour(red, green, blue), stroke);
            dc.SetPen(pen);
            dc.DrawLine(x_c, y_c, x_m, y_m);
        }

        /*
        for (int i = 0; i < global::NUM_CHUNKS - 1; i++) {
            auto m1 = global::SPECTRUM[i];
            auto m2 = global::SPECTRUM[i + 1];

            int width = global::WIDTH / global::NUM_CHUNKS;

            int x1 = i * width;
            int x2 = i * width + width;
            int y1 = global::HEIGHT - m1;
            int y2 = global::HEIGHT - m2;

            wxPen pen_black(wxColour(0, 0, 0), 5);
            wxPen pen_red(wxColour(255, 0, 0), 5);

            dc.SetPen(pen_red);
            dc.DrawLine(x1, y1 + 20, x2, y2 + 20);

            dc.SetPen(pen_black);
            dc.DrawLine(x1, y1, x2, y2);
        }
        */
    }
private:
    wxTimer * timer;
};

#endif
