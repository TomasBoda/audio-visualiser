#include <iostream>
#include <vector>
#include <wx/wx.h>
#include "../config.h"

#ifndef FFT_MUSIC_VISUALISER_WINDOW_H
#define FFT_MUSIC_VISUALISER_WINDOW_H

class Window : public wxFrame {
public:
    Window(const wxString & title, const wxPoint & pos, const wxSize & size) : wxFrame(NULL, wxID_ANY, title, pos, size) {
        timer = new wxTimer(this, wxID_ANY);

        Bind(wxEVT_TIMER, &Window::OnTimer, this, timer->GetId());
        Bind(wxEVT_PAINT, &Window::OnPaint, this);

        timer->Start(50);

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

        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.SetBrush(wxBrush(wxColour(255, 0, 0), wxBRUSHSTYLE_SOLID));

        std::lock_guard<std::mutex> lock(global::MUTEX);

        for (int i = 0; i < global::NUM_CHUNKS; i++) {
            int width = 800 / global::NUM_CHUNKS;
            int height = global::SPECTRUM[i] / 1000;
            int x = i * width;
            int y = 500 - height;

            dc.DrawRectangle(x, y, width, height);
        }
    }
private:
    wxTimer * timer;
};

#endif
