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

        timer->Start(20);

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

        for (int i = 0; i < global::NUM_CHUNKS - 1; i++) {
            auto m1 = global::SPECTRUM[i] / 100;
            auto m2 = global::SPECTRUM[i + 1] / 100;

            int width = global::WIDTH / global::NUM_CHUNKS;

            int x1 = i * width;
            int x2 = i * width + width;
            int y1 = global::HEIGHT - m1;
            int y2 = global::HEIGHT - m2;

            dc.SetPen(*wxWHITE_PEN);
            dc.DrawLine(x1, global::HEIGHT - y1, x2, global::HEIGHT - y2);
        }
    }
private:
    wxTimer * timer;
};

#endif
