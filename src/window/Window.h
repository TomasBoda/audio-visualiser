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

        std::lock_guard<std::mutex> lock(global::MUTEX);
        int shared_data = global::SHARED_DATA;

        dc.DrawText(wxString::Format(wxT("%d"), shared_data), 100, 100);
    }
private:
    wxTimer * timer;
};

#endif
